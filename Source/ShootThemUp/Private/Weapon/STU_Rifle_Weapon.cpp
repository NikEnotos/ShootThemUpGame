// NikotiN Game Studio. All Rights Reserved 


#include "Weapon/STU_Rifle_Weapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

//DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

void ASTU_Rifle_Weapon::StartFire()
{
	//UE_LOG(LogBaseWeapon, Display, TEXT("FIRE"));

	MakeShot();

	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTU_Rifle_Weapon::MakeShot, TimerBetweenShots, true);

}

void ASTU_Rifle_Weapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ASTU_Rifle_Weapon::MakeShot()
{

	if (!GetWorld()) return;

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);

		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Blue, false, 3.0f, 0, 3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 7.0f, 24, FColor::Red, false, 5.0f);

		//UE_LOG(LogBaseWeapon, Display, TEXT("Hit Bone: %s"), *HitResult.BoneName.ToString());
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Blue, false, 3.0f, 0, 3.0f);
	}
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