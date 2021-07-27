// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "STUFindWeaponToPickupTask.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUFindWeaponToPickupTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	USTUFindWeaponToPickupTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AI")
		FBlackboardKeySelector AimLocationKey;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AI")
		FBlackboardKeySelector EnoughClipsKey;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AI")
		float Radius = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		int32 EnoughClips = 3;

};
