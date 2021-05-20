// NikotiN Game Studio. All Rights Reserved 


#include "UI/STU_PlayerHUDWidget.h"
#include "Components/STU_HealthComponent.h"
#include "Components/STU_Weapon_Component.h"

float USTU_PlayerHUDWidget::GetHealthPersent() const
{
	const auto HealthComponent = GetHealthComponent();

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

bool USTU_PlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = GetHealthComponent();
	
	return HealthComponent && !HealthComponent->IsDead();
}

bool USTU_PlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();

	return Controller && Controller->GetStateName() == NAME_Spectating;
}

USTU_Weapon_Component* USTU_PlayerHUDWidget::GetWeaponCoponent() const
{
	const auto Player = GetOwningPlayerPawn();

	if (!Player) return nullptr;

	const auto Component = Player->GetComponentByClass(USTU_Weapon_Component::StaticClass());

	const auto WeaponComponent = Cast<USTU_Weapon_Component>(Component);

	return WeaponComponent;
}

USTU_HealthComponent* USTU_PlayerHUDWidget::GetHealthComponent() const
{
	const auto Player = GetOwningPlayerPawn();

	if (!Player) return nullptr;

	const auto Component = Player->GetComponentByClass(USTU_HealthComponent::StaticClass());

	const auto HealthComponent = Cast<USTU_HealthComponent>(Component);

	return HealthComponent;
}