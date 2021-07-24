// NikotiN Game Studio. All Rights Reserved 


#include "AI/Tasks/STUGetLokationOfNeedAmmoTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STU_Weapon_Component.h"
#include "Pickups/STUAmmoPickup.h"
#include "Weapon/STU_Base_Weapon.h"
#include "Kismet/GameplayStatics.h"

USTUGetLokationOfNeedAmmoTask::USTUGetLokationOfNeedAmmoTask()
{
	NodeName = "Right Ammo for weapon";
}

EBTNodeResult::Type USTUGetLokationOfNeedAmmoTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard) return EBTNodeResult::Failed;

	const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTU_Weapon_Component>(Controller->GetPawn());
	if (!WeaponComponent) return EBTNodeResult::Failed;

	TArray<AActor*> AmmoPickups;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASTUAmmoPickup::StaticClass(), AmmoPickups);

	TArray<ASTUAmmoPickup*> RightAmmoPickups;
	for (auto AmmoPickup : AmmoPickups)
	{
		auto Pickup = Cast<ASTUAmmoPickup>(AmmoPickup);
		if (!Pickup || !Pickup->CouldBeTaken()) continue;

		if (Pickup->GetWeaponType() == ((WeaponComponent->GetCurrentWeapon())->GetClass())) RightAmmoPickups.Add(Pickup);
	}

	if(RightAmmoPickups.Num() == 0) return EBTNodeResult::Failed;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;

	float MinDist = FLT_MAX;

	bool IsSetted = false;

	for (auto Pickup : RightAmmoPickups)
	{
		if (FVector::Dist(Pawn->GetActorLocation(), Pickup->GetActorLocation()) <= Radius && FVector::Dist(Pawn->GetActorLocation(), Pickup->GetActorLocation()) < MinDist)
		{
			MinDist = FVector::Dist(Pawn->GetActorLocation(), Pickup->GetActorLocation());

			Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, Pickup->GetActorLocation());

			IsSetted = true;
		}
	}

	if(!IsSetted) return EBTNodeResult::Failed;

	return EBTNodeResult::Succeeded;
}
