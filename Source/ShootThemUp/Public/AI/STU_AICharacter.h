// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "Player/STU_Character.h"
#include "STU_AICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class SHOOTTHEMUP_API ASTU_AICharacter : public ASTU_Character
{
	GENERATED_BODY()
	
public:

	ASTU_AICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		UBehaviorTree* BehaviorTreeAsset;
};
