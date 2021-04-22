// NikotiN Game Studio. All Rights Reserved 

#include "Weapon/STU_Base_Weapon.h"
#include "Components/SkeletalMeshComponent.h"

ASTU_Base_Weapon::ASTU_Base_Weapon()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}


void ASTU_Base_Weapon::BeginPlay()
{
	Super::BeginPlay();
	
}

