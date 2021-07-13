// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "STUGameModeBase.h"
#include "STUCoreTypes.h"
#include "STUGameModeTeamDomination.generated.h"

class AAIController;

UCLASS()
class SHOOTTHEMUP_API ASTUGameModeTeamDomination : public ASTUGameModeBase
{
	GENERATED_BODY()
	
public:

	ASTUGameModeTeamDomination();

private:


	virtual void SpawnBots() override;

	virtual void ResetOnePlayer(AController* Controller) override;

	virtual void CreateTeamsInfo() override;

	AActor* GetStartSpotOnTeamID(int32 TeamID);
};
