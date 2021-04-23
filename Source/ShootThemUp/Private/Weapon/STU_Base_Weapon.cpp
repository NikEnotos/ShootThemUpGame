// NikotiN Game Studio. All Rights Reserved 

#include "Weapon/STU_Base_Weapon.h"
#include "Components/SkeletalMeshComponent.h"

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
	
}

void ASTU_Base_Weapon::Fire()
{
	UE_LOG(LogBaseWeapon, Display, TEXT("FIRE"));
}

