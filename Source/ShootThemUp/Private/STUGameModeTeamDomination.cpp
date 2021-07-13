// NikotiN Game Studio. All Rights Reserved 

#include "STUGameModeTeamDomination.h"
#include "Player/STU_Character.h"
#include "Player/STU_PlayerController.h"
#include "UI/STUGameHUD.h"
#include "AIController.h"
#include "Player/STUPlayerState.h"
#include "STUUtils.h"
#include "Components/STURespawnComponent.h"
#include "Components/STU_Weapon_Component.h"
#include "EngineUtils.h"

#include "Player/STUPlayerStart.h"
#include "Kismet/GameplayStatics.h"

ASTUGameModeTeamDomination::ASTUGameModeTeamDomination()
{
	DefaultPawnClass = ASTU_Character::StaticClass();
	PlayerControllerClass = ASTU_PlayerController::StaticClass();
	HUDClass = ASTUGameHUD::StaticClass();
	PlayerStateClass = ASTUPlayerState::StaticClass();
}

void ASTUGameModeTeamDomination::SpawnBots()
{
	if (!GetWorld()) return;

	for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
	{
		FActorSpawnParameters SpawnInfo;

		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto STUAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);

		//RestartPlayer(STUAIController);

		//RestartPlayerAtTransform(STUAIController, GetStartSpotOnTeamID(TeamID)->GetActorTransform());
	}


}

AActor* ASTUGameModeTeamDomination::GetStartSpotOnTeamID(int32 TeamID)
{
	TArray<AActor*> StartSpots;

	TArray<AActor*> ReturnedSpots;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASTUPlayerStart::StaticClass(), StartSpots);

	for (const auto StartSpot : StartSpots)
	{
		if (TeamID == Cast<ASTUPlayerStart>(StartSpot)->GetTeamSpawnID())

			ReturnedSpots.Add(StartSpot);

	}

	const auto ReturnedSpot = ReturnedSpots[FMath::Rand() % ReturnedSpots.Num()];

	return ReturnedSpot;
}

void ASTUGameModeTeamDomination::ResetOnePlayer(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}

	const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
	if (!PlayerState) return;

	RestartPlayerAtPlayerStart(Controller, GetStartSpotOnTeamID(PlayerState->GetTeamID()));
	//RestartPlayer(Controller);

	SetPlayerColor(Controller);
}

void ASTUGameModeTeamDomination::CreateTeamsInfo()
{
	if (!GetWorld()) return;

	int32 TeamID = 1;
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->SetTeamID(TeamID);

		PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));

		PlayerState->SetPlayerName(Controller->IsPlayerController() ? "Player" : "Bot");

		//SetPlayerColor(Controller);

		ResetOnePlayer(Controller);

		//RestartPlayerAtPlayerStart(Controller, GetStartSpotOnTeamID(TeamID));

		TeamID = TeamID == 1 ? 2 : 1;
	}

}

