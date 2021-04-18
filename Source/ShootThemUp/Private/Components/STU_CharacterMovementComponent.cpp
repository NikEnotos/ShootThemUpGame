// NikotiN Game Studio. All Rights Reserved 


#include "Components/STU_CharacterMovementComponent.h"
#include "Player/STU_Character.h"

float USTU_CharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const ASTU_Character* Player = Cast<ASTU_Character>(GetPawnOwner());
	return Player && Player->IsRunning() ? MaxSpeed * RunModifier: MaxSpeed;
}