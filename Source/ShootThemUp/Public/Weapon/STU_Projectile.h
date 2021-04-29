// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STU_Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class SHOOTTHEMUP_API ASTU_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	

	ASTU_Projectile();

	void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }


protected:

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
		USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
		UProjectileMovementComponent* MovementComponent;

	virtual void BeginPlay() override;

private:

	FVector ShotDirection;

};
