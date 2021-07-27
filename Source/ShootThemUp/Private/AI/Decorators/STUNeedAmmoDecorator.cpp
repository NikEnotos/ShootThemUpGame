// NikotiN Game Studio. All Rights Reserved 


#include "AI/Decorators/STUNeedAmmoDecorator.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STU_Weapon_Component.h"
#include "Weapon/STU_Base_Weapon.h"
#include "BehaviorTree/BlackboardComponent.h"

USTUNeedAmmoDecorator::USTUNeedAmmoDecorator()
{
	NodeName = "Need Ammo";
}

bool USTUNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller || !Blackboard) return false;

	const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTU_Weapon_Component>(Controller->GetPawn());
	if (!WeaponComponent) return false;

	WeaponComponent->SetWantToPickupWeapon(WeaponComponent->NeedAmmo((WeaponComponent->GetCurrentWeapon())->GetClass(), EnoughClips));

	Blackboard->SetValueAsInt(EnoughClipsKey.SelectedKeyName, EnoughClips);

	return WeaponComponent->NeedAmmo((WeaponComponent->GetCurrentWeapon())->GetClass(), EnoughClips);

	//return WeaponComponent->NeedAmmo(WeaponType);
}
