// NikotiN Game Studio. All Rights Reserved 


#include "AI/STU_AICharacter.h"
#include "AI/STU_AIController.h"

ASTU_AICharacter::ASTU_AICharacter(const FObjectInitializer& ObjInit):Super(ObjInit)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AIControllerClass = ASTU_AIController::StaticClass();
}