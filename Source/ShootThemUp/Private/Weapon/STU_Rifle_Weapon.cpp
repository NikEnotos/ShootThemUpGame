// NikotiN Game Studio. All Rights Reserved 


#include "Weapon/STU_Rifle_Weapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Component/STUWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

//DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

ASTU_Rifle_Weapon::ASTU_Rifle_Weapon()
{
	WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTU_Rifle_Weapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponFXComponent);
}

void ASTU_Rifle_Weapon::StartFire()
{
	InitFX();

	//UE_LOG(LogBaseWeapon, Display, TEXT("FIRE"));
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTU_Rifle_Weapon::MakeShot, TimerBetweenShots, true);

	MakeShot();
}

void ASTU_Rifle_Weapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);

	SetFXActive(false);

}

void ASTU_Rifle_Weapon::MakeShot()
{

	if (!GetWorld() || IsAmmoEmpty()) return;

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	FVector TraceFXEnd = TraceEnd;

	if (HitResult.bBlockingHit)
	{
		TraceFXEnd = HitResult.ImpactPoint;

		MakeDamage(HitResult);

		//DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Blue, false, 3.0f, 0, 3.0f);
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 7.0f, 24, FColor::Red, false, 5.0f);

		WeaponFXComponent->PlayImpactFX(HitResult);

		//UE_LOG(LogBaseWeapon, Display, TEXT("Hit Bone: %s"), *HitResult.BoneName.ToString());
	}

	SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);

	DecreaseAmmo();

	//UGameplayStatics::SpawnSoundAtLocation(GetWorld(), FireSound, GetMuzzleWorldLocation());
}

bool ASTU_Rifle_Weapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

																//const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
	TraceStart = ViewLocation;																							//SocketTransform.GetLocation();
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);	//Convert value from degrees in our property to Radians
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);									//SocketTransform.GetRotation().GetForwardVector();
	TraceEnd = TraceStart + ShootDirection * ShotDistance;
	return true;																										//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Blue, false, 3.0f, 0, 3.0f);
}

void ASTU_Rifle_Weapon::MakeDamage(const FHitResult& HitResult)
{
	const auto DamagedActor = HitResult.GetActor();
	if (!DamagedActor) return;

	DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetController(), this);
}

void ASTU_Rifle_Weapon::InitFX()
{
	if (!MuzzleFXComponent)
	{
		MuzzleFXComponent = SpawnMuzzleFX();
	}

	if (!FireAudioComponent)
	{
		FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);															 /*, GetMuzzleWorldLocation(), WeaponMesh->GetSocketRotation(MuzzleSocketName), EAttachLocation::SnapToTarget*/
	}

	SetFXActive(true);

}

void ASTU_Rifle_Weapon::SetFXActive(bool IsActive)
{
	if (MuzzleFXComponent)
	{
		MuzzleFXComponent->SetPaused(!IsActive);

		MuzzleFXComponent->SetVisibility(IsActive, true);
	}

	if (FireAudioComponent)
	{
		FireAudioComponent->SetPaused(!IsActive);
	}
}

void ASTU_Rifle_Weapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
	const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);

	if (TraceFXComponent)
	{
		TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
	}
}


AController* ASTU_Rifle_Weapon::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}

void ASTU_Rifle_Weapon::Zoom(bool Enabled)
{
	const auto Controller = Cast<APlayerController>(GetController());
	if (!Controller || !Controller->PlayerCameraManager) return;

	if (Enabled)
	{
		DefaultCameraFOV = Controller->PlayerCameraManager->GetFOVAngle();
	}

	Controller->PlayerCameraManager->SetFOV(Enabled ? FeeidOfViewZoomAngle : DefaultCameraFOV);
	
}
