// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STU_PlayerController.generated.h"

class USTURespawnComponent;

UCLASS()
class SHOOTTHEMUP_API ASTU_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ASTU_PlayerController();

protected:
		
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
		USTURespawnComponent* RespawnComponent;

	virtual void OnPossess(APawn* InPawn) override;

};
