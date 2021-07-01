// NikotiN Game Studio. All Rights Reserved 


#include "Player/STU_PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/STU_Weapon_Component.h"

ASTU_PlayerCharacter::ASTU_PlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

}

// Called to bind functionality to input
void ASTU_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	check(WeaponComponent);
	check(GetCapsuleComponent())

	PlayerInputComponent->BindAxis("MoveForward", this, &ASTU_PlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTU_PlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASTU_PlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTU_PlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTU_PlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTU_PlayerCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTU_PlayerCharacter::OnStopRunning);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTU_Weapon_Component::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTU_Weapon_Component::StopFire);
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USTU_Weapon_Component::NextWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USTU_Weapon_Component::Reload);

}

void ASTU_PlayerCharacter::MoveForward(float Amount)
{
	IsMovingForward = Amount > 0.0f;

	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTU_PlayerCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void ASTU_PlayerCharacter::OnStartRunning()
{
	WeaponComponent->CharIsRuning = true;
	WantsToRun = true;
}

void ASTU_PlayerCharacter::OnStopRunning()
{
	WeaponComponent->CharIsRuning = false;
	WantsToRun = false;
}

bool ASTU_PlayerCharacter::IsRunning() const
{
	return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

void ASTU_PlayerCharacter::OnDeath()
{
	Super::OnDeath();

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
	
}
