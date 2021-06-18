// NikotiN Game Studio. All Rights Reserved 


#include "AI/STU_AICharacter.h"
#include "AI/STU_AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/STU_AIWeapon_Component.h"
#include "BrainComponent.h"

ASTU_AICharacter::ASTU_AICharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<USTU_AIWeapon_Component>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::Disabled;

	AIControllerClass = ASTU_AIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}

}

void ASTU_AICharacter::OnDeath()
{
	Super::OnDeath();

	const auto STUController = Cast<AAIController>(Controller);
	if (STUController && STUController->BrainComponent)
	{
		STUController->BrainComponent->Cleanup();
	}
}