// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STUFireService.generated.h"

class USTU_Weapon_Component;

UCLASS()
class SHOOTTHEMUP_API USTUFireService : public UBTService
{
	GENERATED_BODY()
	
public:

	USTUFireService();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float DistanceToAutofire = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float MinDelayToShot = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float MaxDelayToShot = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		FBlackboardKeySelector EnemyActorKey;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AI")
		FBlackboardKeySelector EnemyLocationKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
