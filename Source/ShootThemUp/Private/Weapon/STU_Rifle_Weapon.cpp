// NikotiN Game Studio. All Rights Reserved 


#include "Weapon/STU_Rifle_Weapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Component/STUWeaponFXComponent.h"
#include "NiagaraComponent.h"

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
	InitMuzzleFX();

	//UE_LOG(LogBaseWeapon, Display, TEXT("FIRE"));
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTU_Rifle_Weapon::MakeShot, TimerBetweenShots, true);

	MakeShot();
}

void ASTU_Rifle_Weapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);

	SetMuzzleFXVisible(false);
}

void ASTU_Rifle_Weapon::MakeShot()
{

	if (!GetWorld() || IsAmmoEmpty()) return;

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);

		//DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Blue, false, 3.0f, 0, 3.0f);
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 7.0f, 24, FColor::Red, false, 5.0f);

		WeaponFXComponent->PlayImpactFX(HitResult);

		//UE_LOG(LogBaseWeapon, Display, TEXT("Hit Bone: %s"), *HitResult.BoneName.ToString());
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Blue, false, 3.0f, 0, 3.0f);
	}

	DecreaseAmmo();
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
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;																										//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Blue, false, 3.0f, 0, 3.0f);
}

void ASTU_Rifle_Weapon::MakeDamage(const FHitResult& HitResult)
{
	const auto DamagedActor = HitResult.GetActor();
	if (!DamagedActor) return;

	DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}

void ASTU_Rifle_Weapon::InitMuzzleFX()
{
	if (!MuzzleFXComponent)
	{
		MuzzleFXComponent = SpawnMuzzleFX();
	}

	SetMuzzleFXVisible(true);

}

void ASTU_Rifle_Weapon::SetMuzzleFXVisible(bool Visible)
{
	if (MuzzleFXComponent)
	{
		//MuzzleFXComponent->SetPaused(!Visible);

		MuzzleFXComponent->SetVisibility(Visible, true);
	}
}