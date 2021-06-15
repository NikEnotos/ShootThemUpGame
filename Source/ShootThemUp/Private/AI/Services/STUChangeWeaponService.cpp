// NikotiN Game Studio. All Rights Reserved 


#include "AI/Services/STUChangeWeaponService.h"
#include "Components/STU_Weapon_Component.h"
#include "AIController.h"
#include "STUUtils.h"


USTUChangeWeaponService::USTUChangeWeaponService()
{
	NodeName = "Change Weapon";
}

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();

	if (Controller)
	{
		const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTU_Weapon_Component>(Controller->GetPawn());
		
		if (WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
		{
			WeaponComponent->NextWeapon();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}