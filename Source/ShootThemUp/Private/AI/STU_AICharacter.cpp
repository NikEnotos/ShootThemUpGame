// NikotiN Game Studio. All Rights Reserved 


#include "AI/STU_AICharacter.h"
#include "AI/STU_AIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ASTU_AICharacter::ASTU_AICharacter(const FObjectInitializer& ObjInit):Super(ObjInit)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AIControllerClass = ASTU_AIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}

}