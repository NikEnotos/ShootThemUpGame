// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "STUPlayerStart.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUPlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:

	int32 GetTeamSpawnID() { return TeamSpawnID; }

private:

	UPROPERTY(EditAnywhere, Category = "TeamID", meta = (ClampMin = "1", ClampMax = "2")) 
		int32 TeamSpawnID = 1;
};