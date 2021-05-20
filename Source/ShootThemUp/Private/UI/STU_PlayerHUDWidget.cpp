// NikotiN Game Studio. All Rights Reserved 


#include "UI/STU_PlayerHUDWidget.h"
#include "Components/STU_HealthComponent.h"
#include "Components/STU_Weapon_Component.h"

float USTU_PlayerHUDWidget::GetHealthPersent() const
{
	const auto Player = GetOwningPlayerPawn();

	if (!Player) return 0.0f;

	const auto Component = Player->GetComponentByClass(USTU_HealthComponent::StaticClass());

	const auto HealthComponent = Cast<USTU_HealthComponent>(Component);

	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool USTU_PlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = GetWeaponCoponent();

	if (!WeaponComponent) return false;

	return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool USTU_PlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = GetWeaponCoponent();

	if (!WeaponComponent) return false;

	return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}

USTU_Weapon_Component* USTU_PlayerHUDWidget::GetWeaponCoponent() const
{
	const auto Player = GetOwningPlayerPawn();

	if (!Player) return nullptr;

	const auto Component = Player->GetComponentByClass(USTU_Weapon_Component::StaticClass());

	const auto WeaponComponent = Cast<USTU_Weapon_Component>(Component);

	return WeaponComponent;
}