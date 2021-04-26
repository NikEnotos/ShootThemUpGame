// NikotiN Game Studio. All Rights Reserved 


#include "Components/STU_Weapon_Component.h"
#include "Weapon/STU_Base_Weapon.h"
#include "GameFramework/Character.h"

USTU_Weapon_Component::USTU_Weapon_Component()
{

	PrimaryComponentTick.bCanEverTick = false;

}


void USTU_Weapon_Component::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
	
}

void USTU_Weapon_Component::SpawnWeapon()
{
	if (!GetWorld())return;

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	CurrentWeapon = GetWorld()->SpawnActor<ASTU_Base_Weapon>(WeaponClass);
	if (!CurrentWeapon) return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
	CurrentWeapon->SetOwner(Character);
	
}

void USTU_Weapon_Component::Fire()
{
	
	if (!CurrentWeapon) return;

	CurrentWeapon->Fire();

}
