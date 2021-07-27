// NikotiN Game Studio. All Rights Reserved 


#include "AI/Tasks/STUFindWeaponToPickupTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Weapon/STU_Base_Weapon.h"
#include "Kismet/GameplayStatics.h"

#include "AI/Decorators/STUNeedAmmoDecorator.h"

USTUFindWeaponToPickupTask::USTUFindWeaponToPickupTask()
{
	NodeName = "Find Weapon To Pickup";
}

EBTNodeResult::Type USTUFindWeaponToPickupTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard) return EBTNodeResult::Failed;

	TArray<AActor*> WeaponPickups;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASTU_Base_Weapon::StaticClass(), WeaponPickups);

	if (WeaponPickups.Num() == 0) return EBTNodeResult::Failed;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;

	float MinDist = FLT_MAX;

	bool IsSetted = false;

	for (auto Pickup : WeaponPickups)
	{
		if (Cast<ASTU_Base_Weapon>(Pickup)->GetIsDropped() && Cast<ASTU_Base_Weapon>(Pickup)->GetAmmoData().Clips >= Blackboard->GetValueAsInt(EnoughClipsKey.SelectedKeyName) && FVector::Dist(Pawn->GetActorLocation(), Pickup->GetActorLocation()) <= Radius && FVector::Dist(Pawn->GetActorLocation(), Pickup->GetActorLocation()) < MinDist)
		{
			MinDist = FVector::Dist(Pawn->GetActorLocation(), Pickup->GetActorLocation());

			Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, Pickup->GetActorLocation());

			IsSetted = true;
		}
	}

	if (!IsSetted) return EBTNodeResult::Failed;

	return EBTNodeResult::Succeeded;
}