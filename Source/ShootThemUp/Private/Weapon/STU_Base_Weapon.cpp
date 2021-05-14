// NikotiN Game Studio. All Rights Reserved 

#include "Weapon/STU_Base_Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

ASTU_Base_Weapon::ASTU_Base_Weapon()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}


void ASTU_Base_Weapon::BeginPlay()
{
	Super::BeginPlay();
	
	check(WeaponMesh);

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

APlayerController* ASTU_Base_Weapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player) return nullptr;

	return Player->GetController<APlayerController>();
}

bool ASTU_Base_Weapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto Controller = GetPlayerController();
	if (!Controller) return false;

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
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
	LogAmmo();

	if (IsClipEmpty() && !IsAmmoEmpty())
	{
		StopFire();
		OnClipEmpty.Broadcast();
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

	UE_LOG(LogBaseWeapon, Display, TEXT("--------CHANGE CLIP--------"));
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
