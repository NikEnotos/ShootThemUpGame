// NikotiN Game Studio. All Rights Reserved 


#include "AI/STU_AICharacter.h"
#include "AI/STU_AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/STU_AIWeapon_Component.h"

ASTU_AICharacter::ASTU_AICharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<USTU_AIWeapon_Component>("WeaponComponent"))
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