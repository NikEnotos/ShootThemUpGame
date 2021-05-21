// NikotiN Game Studio. All Rights Reserved 


#include "UI/STU_PlayerHUDWidget.h"
#include "Components/STU_HealthComponent.h"
#include "Components/STU_Weapon_Component.h"
#include "STUUtils.h"

float USTU_PlayerHUDWidget::GetHealthPersent() const
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTU_HealthComponent>(GetOwningPlayerPawn());

	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool USTU_PlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTU_Weapon_Component>(GetOwningPlayerPawn());

	if (!WeaponComponent) return false;

	return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool USTU_PlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTU_Weapon_Component>(GetOwningPlayerPawn());

	if (!WeaponComponent) return false;

	return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}

bool USTU_PlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTU_HealthComponent>(GetOwningPlayerPawn());
	
	return HealthComponent && !HealthComponent->IsDead();
}

bool USTU_PlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();

	return Controller && Controller->GetStateName() == NAME_Spectating;
}
