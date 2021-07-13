// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STUCoreTypes.h"
#include "STUGameModeBase.generated.h"

class AAIController;

UCLASS()
class SHOOTTHEMUP_API ASTUGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	ASTUGameModeBase();

	FOnMatchStateChangedSignature OnMatchStateChanged;

	virtual void StartPlay() override;

	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	void Killed(AController* KillerController, AController* VictimController);

	FGameData GetGameData() { return GameData; }

	int32 GetCurrentRoundNum() { return CurrentRound; }

	int32 GetRoundSecondsRemaining() { return RoundCountDown; }

	void RespawnRequest(AController* Controller);

	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;

	virtual bool ClearPause() override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Game")
		TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
		TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
		FGameData GameData;

	virtual void SpawnBots();

	virtual void ResetOnePlayer(AController* Controller);

	virtual void CreateTeamsInfo();

	FLinearColor DetermineColorByTeamID(int32 TeamID) const;

	void SetPlayerColor(AController* Controller);

private:

	ESTUMatchState MatchState = ESTUMatchState::WaitingToStart;

	int32 CurrentRound = 1;
	int32 RoundCountDown = 0;

	FTimerHandle GameRoundTimerHandle;

	void StartRound();

	void GameTimerUpdate();

	void ResetPlayers();

	//void ResetOnePlayer(AController* Controller);

	//void CreateTeamsInfo();

	void LogPlayerInfo();

	void StartRespawn(AController* Controller);

	void GameOver();

	void SetMatchState(ESTUMatchState State);

	void StopAllFire();

	//AActor* GetStartSpotOnTeamID(int32 TeamID);
};
