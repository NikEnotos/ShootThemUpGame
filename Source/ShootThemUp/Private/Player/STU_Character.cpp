// NikotiN Game Studio. All Rights Reserved 


#include "Player/STU_Character.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/STU_CharacterMovementComponent.h"
#include "Components/STU_HealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/STU_Weapon_Component.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"

// Sets default values
ASTU_Character::ASTU_Character(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<USTU_CharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<USTU_HealthComponent>("HealthComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());

	WeaponComponent = CreateDefaultSubobject<USTU_Weapon_Component>("WeaponComponent");

}

// Called when the game starts or when spawned
void ASTU_Character::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(HealthTextComponent);
	check(GetCharacterMovement());
	check(GetMesh());

	OnHelthChanged(HealthComponent->GetHealth(), 0.0f);
	HealthComponent->OnDeath.AddUObject(this, &ASTU_Character::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ASTU_Character::OnHelthChanged);

	LandedDelegate.AddDynamic(this, &ASTU_Character::OnGroundLanded);

}

void ASTU_Character::OnHelthChanged(float Health, float HealthDelta)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

// Called every frame
void ASTU_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASTU_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	check(WeaponComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASTU_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTU_Character::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASTU_Character::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTU_Character::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTU_Character::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTU_Character::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTU_Character::OnStopRunning);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTU_Weapon_Component::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTU_Weapon_Component::StopFire);
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USTU_Weapon_Component::NextWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USTU_Weapon_Component::Reload);

}

void ASTU_Character::MoveForward(float Amount) 
{
	IsMovingForward = Amount > 0.0f;

	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTU_Character::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void ASTU_Character::OnStartRunning()
{
	WeaponComponent->CharIsRuning = true;
	WantsToRun = true;
}

void ASTU_Character::OnStopRunning()
{
	WeaponComponent->CharIsRuning = false;
	WantsToRun = false;
}

bool ASTU_Character::IsRunning() const
{
	return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

float  ASTU_Character::GetMovementDirection() const
{
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);

	return FMath::RadiansToDegrees(AngleBetween) * FMath::Sign(CrossProduct.Z); 
}

void ASTU_Character::OnDeath()
{
	WeaponComponent->StopFire();

	//PlayAnimMontage(DeathAnimMontage);

	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(LifeSpanOnDeath); //Destroy Actor in 5 sec

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

void ASTU_Character::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetCharacterMovement()->Velocity.Z;

	if (FallVelocityZ < LandedDamageVelocity.X) return;

	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);

	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}

void ASTU_Character::SetPlayerColor(const FLinearColor& Color)
{
	const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
	if (!MaterialInst) return;

	MaterialInst->SetVectorParameterValue(MaterialColorName, Color);

}

