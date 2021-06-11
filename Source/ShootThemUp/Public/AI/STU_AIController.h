// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STU_AIController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTU_AIController : public AAIController
{
	GENERATED_BODY()
	
protected:

	virtual void OnPossess(APawn* InPawn) override;

};
