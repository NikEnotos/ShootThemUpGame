// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "STUGetLokationOfNeedAmmoTask.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUGetLokationOfNeedAmmoTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	USTUGetLokationOfNeedAmmoTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AI")
		FBlackboardKeySelector AimLocationKey;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AI")
		float Radius = 1000.0f;

};
