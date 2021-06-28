// NikotiN Game Studio. All Rights Reserved 


#include "AI/STU_AIController.h"
#include "AI/STU_AICharacter.h"
#include "Components/STUAIPerceptionComponent.h"
#include "Components/STURespawnComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ASTU_AIController::ASTU_AIController()
{
	STUAIPerceptionComponent = CreateDefaultSubobject<USTUAIPerceptionComponent>("STUAIPerceptionComponent");
	SetPerceptionComponent(*STUAIPerceptionComponent);

	RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("RespawnComponent");

	bWantsPlayerState = true;
}

void ASTU_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const auto AimActor = GetFocusOnActor();

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

AActor* ASTU_AIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;
	
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));

}