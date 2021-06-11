// NikotiN Game Studio. All Rights Reserved 


#include "AI/STU_AIController.h"
#include "AI/STU_AICharacter.h"

void ASTU_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto STUCharacter = Cast<ASTU_AICharacter>(InPawn);

	if (STUCharacter)
	{
		RunBehaviorTree(STUCharacter->BehaviorTreeAsset);
	}
}