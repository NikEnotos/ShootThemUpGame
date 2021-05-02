// NikotiN Game Studio. All Rights Reserved 


#include "Weapon/STU_Launcher_Weapon.h"
#include "Weapon/STU_Projectile.h"

void ASTU_Launcher_Weapon::StartFire()
{
	MakeShot();
}

void ASTU_Launcher_Weapon::MakeShot()
{	
	if (!GetWorld()) return;

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());

	ASTU_Projectile*  Projectile = GetWorld()->SpawnActorDeferred<ASTU_Projectile>(ProjectileClass, SpawnTransform); //prespawn projecile 

	if (Projectile)
	{
		Projectile->SetShotDirection(Direction);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform); 
	}
}

