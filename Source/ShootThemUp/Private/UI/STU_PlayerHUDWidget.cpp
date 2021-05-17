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

bool USTU_PlayerHUDWidget::GetWeaponUIData(FweaponUIData& UIData) const
{
	const auto Player = GetOwningPlayerPawn();

	if (!Player) return false;

	const auto Component = Player->GetComponentByClass(USTU_Weapon_Component::StaticClass());

	const auto WeaponComponent = Cast<USTU_Weapon_Component>(Component);

	if (!WeaponComponent) return false;

	return WeaponComponent->GetWeaponUIData(UIData);
}