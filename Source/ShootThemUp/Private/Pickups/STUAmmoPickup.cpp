// NikotiN Game Studio. All Rights Reserved 


#include "Pickups/STUAmmoPickup.h"
#include "Components/STU_Weapon_Component.h"
#include "Components/STU_HealthComponent.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool ASTUAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent <USTU_HealthComponent>(PlayerPawn);

	if (!HealthComponent || HealthComponent->IsDead()) return false;

	const auto WeaponComponent = STUUtils::GetSTUPlayerComponent <USTU_Weapon_Component>(PlayerPawn);

	if (!WeaponComponent) return false;

	UE_LOG(LogAmmoPickup, Display, TEXT("Ammo was taken"));

	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}