// NikotiN Game Studio. All Rights Reserved 


#include "AI/STU_AIController.h"
#include "AI/STU_AICharacter.h"
#include "Components/STUAIPerceptionComponent.h"

ASTU_AIController::ASTU_AIController()
{
	STUAIPerceptionComponent = CreateDefaultSubobject<USTUAIPerceptionComponent>("STUAIPerceptionComponent");
	SetPerceptionComponent(*STUAIPerceptionComponent);
}

void ASTU_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const auto AimActor = STUAIPerceptionComponent->GetClosestEnemy();

	SetFocus(AimActor);
}

void ASTU_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto STUCharacter = Cast<ASTU_AICharacter>(InPawn);

	if (STUCharacter)
	{
		RunBehaviorTree(STUCharacter->BehaviorTreeAsset);
	}
}