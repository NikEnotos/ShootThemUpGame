// NikotiN Game Studio. All Rights Reserved 

#include "Weapon/STU_Base_Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "STU_Character.h"
#include "Player/STU_PlayerCharacter.h"
#include "STUUtils.h"
#include "Components/STU_Weapon_Component.h"
#include "UI/DropWeaponInfoWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

ASTU_Base_Weapon::ASTU_Base_Weapon()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	WeaponMesh->SetSimulatePhysics(true);


	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(70.0f);
	//CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CollisionComponent->SetupAttachment(GetRootComponent());


	WeaponWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WeaponWidgetComponent");
	WeaponWidgetComponent->SetupAttachment(GetRootComponent());
	WeaponWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WeaponWidgetComponent->SetDrawAtDesiredSize(true);
	WeaponWidgetComponent->SetVisibility(false);

}


void ASTU_Base_Weapon::BeginPlay()
{
	Super::BeginPlay();
	
	checkf(DefaultAmmo.Bullets > 0, TEXT("Bullets count coudn`t be less or equal zero"));
	checkf(DefaultAmmo.Clips > 0, TEXT("Clips count coudn`t be less or equal zero"));
	check(WeaponMesh);

	const auto WeaponWidget = Cast<UDropWeaponInfoWidget>(WeaponWidgetComponent->GetUserWidgetObject());
	if (WeaponWidget) WeaponWidget->SetDroppedWeaponUIData(GetUIData());
	

	CurrentAmmo = DefaultAmmo;
}

void ASTU_Base_Weapon::StartFire()
{

}

void ASTU_Base_Weapon::StopFire()
{

}

void ASTU_Base_Weapon::MakeShot()
{
	
}

bool ASTU_Base_Weapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto STUCharacter = Cast<ACharacter>(GetOwner());

	if (!STUCharacter) return false;

	if (STUCharacter->IsPlayerControlled())
	{ 
		const auto Controller = STUCharacter->GetController<APlayerController>();

		if (!Controller) return false;

		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}
	else
	{
		ViewLocation = GetMuzzleWorldLocation();
		ViewRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
	}

	return true;
}

FVector ASTU_Base_Weapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ASTU_Base_Weapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const 
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

																							//const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
	TraceStart = ViewLocation;																//SocketTransform.GetLocation();

	const FVector ShootDirection = ViewRotation.Vector();									//SocketTransform.GetRotation().GetForwardVector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;																			//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Blue, false, 3.0f, 0, 3.0f);
}

void ASTU_Base_Weapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) 
{
	if (!GetWorld()) return;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	CollisionParams.bReturnPhysicalMaterial = true;										   // for return Physical material in HitResult

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);

}

void ASTU_Base_Weapon::DecreaseAmmo()
{
	if (CurrentAmmo.Bullets == 0)
	{
		UE_LOG(LogBaseWeapon, Warning, TEXT("Clip is empty"));
		return;
	}

	CurrentAmmo.Bullets--;
	//LogAmmo();

	if (IsClipEmpty() && !IsAmmoEmpty())
	{
		StopFire();
		OnClipEmpty.Broadcast(this);
	}

}

bool ASTU_Base_Weapon::IsAmmoEmpty() const
{
	return !CurrentAmmo.Infinet && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool ASTU_Base_Weapon::IsClipEmpty() const
{
	return CurrentAmmo.Bullets == 0;
}

void ASTU_Base_Weapon::ChangeClip()
{
	if (!CurrentAmmo.Infinet)
	{
		if (CurrentAmmo.Clips == 0)
		{
			UE_LOG(LogBaseWeapon, Warning, TEXT("No more Clips"));
			return;
		}

		CurrentAmmo.Clips--;
	}
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;

	//UE_LOG(LogBaseWeapon, Display, TEXT("--------CHANGE CLIP--------"));
}

bool ASTU_Base_Weapon::CanReload() const
{
	return CurrentAmmo.Bullets < DefaultAmmo.Bullets&& CurrentAmmo.Clips > 0;
}

void ASTU_Base_Weapon::LogAmmo()
{
	FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
	AmmoInfo += CurrentAmmo.Infinet ? "Infinet" : FString::FromInt(CurrentAmmo.Clips);
	UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfo);
}

bool ASTU_Base_Weapon::ISAmmoFull() const
{
	return CurrentAmmo.Clips == DefaultAmmo.Clips && CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

bool ASTU_Base_Weapon::TryToAddAmmo(int32 ClipsAmount)
{
	if (CurrentAmmo.Infinet || ISAmmoFull() || ClipsAmount <= 0) return false;

	if (IsAmmoEmpty())
	{
		UE_LOG(LogBaseWeapon, Display, TEXT("Ammo was empty!"));
		CurrentAmmo.Clips = FMath::Clamp(CurrentAmmo.Clips + ClipsAmount, 0, DefaultAmmo.Clips + 1);
		OnClipEmpty.Broadcast(this);
	}
	else if (CurrentAmmo.Clips < DefaultAmmo.Clips)
	{
		const auto NextClipAmount = CurrentAmmo.Clips + ClipsAmount;
		if (DefaultAmmo.Clips - NextClipAmount >= 0)
		{
			CurrentAmmo.Clips = NextClipAmount;
			UE_LOG(LogBaseWeapon, Display, TEXT("Clips were added!"));
		}
		else
		{
			CurrentAmmo.Clips = DefaultAmmo.Clips;
			CurrentAmmo.Bullets = DefaultAmmo.Bullets;
			UE_LOG(LogBaseWeapon, Display, TEXT("Ammo is full now!"));
		}
	}
	else
	{
		CurrentAmmo.Bullets = DefaultAmmo.Bullets;
		UE_LOG(LogBaseWeapon, Display, TEXT("Bullets were empty!"));
	}
	return true;
}

UNiagaraComponent* ASTU_Base_Weapon::SpawnMuzzleFX()
{
	return UNiagaraFunctionLibrary::SpawnSystemAttached(	//
		MuzzleFX,											//
		WeaponMesh,											//
		MuzzleSocketName,									//
		FVector::ZeroVector,								//
		FRotator::ZeroRotator,								//
		EAttachLocation::SnapToTarget,						//
		true);
}

void ASTU_Base_Weapon::NotifyActorBeginOverlap(AActor* OtherActor)
{	Super::NotifyActorBeginOverlap(OtherActor);

	if (!Cast<ASTU_Character>(OtherActor)) return;


	UE_LOG(LogBaseWeapon, Display, TEXT("--------BEGIN OVERLAP--------"));

	const auto STUPlayerCharacter = Cast<ASTU_PlayerCharacter>(OtherActor);
	if(STUPlayerCharacter)
	{
		InfoOnPickup(true);
	}

	/////////////////////////////////////////////////SetSimulatePhysicsForDrop(false);
	SetSimulatePhysicsForDrop(true);

	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTU_Weapon_Component>(OtherActor);
	if (WeaponComponent) WeaponComponent->SetCanPickup(true);


}

void ASTU_Base_Weapon::NotifyActorEndOverlap(AActor* OtherActor)
{	Super::NotifyActorEndOverlap(OtherActor);

	if (!Cast<ASTU_Character>(OtherActor)) return;


	const auto STUPlayerCharacter = Cast<ASTU_PlayerCharacter>(OtherActor);
	if (STUPlayerCharacter)
	{
		InfoOnPickup(false);
	}

	SetSimulatePhysicsForDrop(true);

	const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTU_Weapon_Component>(OtherActor);
	if (WeaponComponent) WeaponComponent->SetCanPickup(false);


	UE_LOG(LogBaseWeapon, Display, TEXT("--------END OVERLAP--------"));

}

void ASTU_Base_Weapon::InfoOnPickup(bool IsVisible)
{
	WeaponWidgetComponent->SetVisibility(IsVisible);

	WeaponMesh->SetRenderCustomDepth(IsVisible);
}

void ASTU_Base_Weapon::SetSimulatePhysicsForDrop(bool IsSimulate)
{
/*	if(IsSimulate) WeaponMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	if(!IsSimulate) */
	
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	WeaponMesh->SetSimulatePhysics(IsSimulate);
}

void ASTU_Base_Weapon::SetCollisionForWeaponOnHand()
{
	WeaponMesh->SetSimulatePhysics(false);

	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WeaponMesh->SetNotifyRigidBodyCollisionBelow(false);
	

	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void ASTU_Base_Weapon::IsPickupped(bool IsPiskupped)
{
	if (IsPiskupped) Destroy();
}

void ASTU_Base_Weapon::MakeSingleShot()
{

}

bool ASTU_Base_Weapon::LeftLittleAmmo(int32 EnoughClips)
{
	return CurrentAmmo.Clips < EnoughClips;
}