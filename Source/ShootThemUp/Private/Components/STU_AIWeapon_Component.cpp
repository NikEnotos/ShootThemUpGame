// NikotiN Game Studio. All Rights Reserved 


#include "Components/STU_AIWeapon_Component.h"
#include "Weapon/STU_Base_Weapon.h"

void USTU_AIWeapon_Component::StartFire()
{
	if (!CanFire()) return;

	if (CurrentWeapon->IsAmmoEmpty())
	{
		CurrentWeapon->StopFire();
		NextWeapon();
	}
	else 
	{
		CurrentWeapon->StartFire();
	}
}

void USTU_AIWeapon_Component::NextWeapon()
{
	if (!CanEquip()) return;

	int32 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();

	while (NextIndex != CurrentWeaponIndex)
	{
		if (!Weapons[NextIndex]->IsAmmoEmpty()) break;

		NextIndex = (NextIndex + 1) % Weapons.Num();
	}

	if (Weapons[NextIndex] != CurrentWeapon)
	{
		CurrentWeaponIndex = NextIndex;
		EquipWeapon(CurrentWeaponIndex);
	}

}