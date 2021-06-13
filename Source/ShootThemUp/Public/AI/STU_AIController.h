// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STU_AIController.generated.h"

class USTUAIPerceptionComponent;

UCLASS()
class SHOOTTHEMUP_API ASTU_AIController : public AAIController
{
	GENERATED_BODY()
	
public:

	ASTU_AIController();

protected:

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
		USTUAIPerceptionComponent* STUAIPerceptionComponent;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;
};
