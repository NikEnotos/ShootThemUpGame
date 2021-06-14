// NikotiN Game Studio. All Rights Reserved 


#include "AI/Services/STUFireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STU_Weapon_Component.h"
#include "STUUtils.h"
#include "Components/STU_HealthComponent.h"

USTUFireService::USTUFireService()
{
	NodeName = "Fire";
}

void USTUFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	const auto Pawn = Controller->GetPawn();
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTU_HealthComponent>(Pawn);

	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if (Controller)
	{
		const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTU_Weapon_Component>(Controller->GetPawn());

		if (WeaponComponent && !HealthComponent->IsDead())
		{
			HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

