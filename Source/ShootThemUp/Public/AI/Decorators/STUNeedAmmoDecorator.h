// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STUNeedAmmoDecorator.generated.h"

class ASTU_Base_Weapon;

UCLASS()
class SHOOTTHEMUP_API USTUNeedAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:

	USTUNeedAmmoDecorator();

protected:

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		//TSubclassOf<ASTU_Base_Weapon> WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		int32 EnoughClips = 3;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		FBlackboardKeySelector EnoughClipsKey;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
