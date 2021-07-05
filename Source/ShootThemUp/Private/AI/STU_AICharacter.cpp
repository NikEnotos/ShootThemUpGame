// NikotiN Game Studio. All Rights Reserved 


#include "AI/STU_AICharacter.h"
#include "AI/STU_AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/STU_AIWeapon_Component.h"
#include "BrainComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/STUHealthBarWidget.h"
#include "Components/STU_HealthComponent.h"

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

	if (ShowHealthBar)
	{
		HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
		HealthWidgetComponent->SetupAttachment(GetRootComponent());
		HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		HealthWidgetComponent->SetDrawAtDesiredSize(true);
	}
}

void ASTU_AICharacter::BeginPlay()
{
	Super::BeginPlay();

	if(ShowHealthBar) check(HealthWidgetComponent);
}

void ASTU_AICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ShowHealthBar)
	{
		UpdateHealthWidgetVisibility();
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

void ASTU_AICharacter::OnHelthChanged(float Health, float HealthDelta)
{
	Super::OnHelthChanged(Health, HealthDelta);

	if (ShowHealthBar)
	{
		const auto HealthBarWidget = Cast<USTUHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
		if (!HealthBarWidget) return;

		HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
	}
}

void ASTU_AICharacter::UpdateHealthWidgetVisibility()
{
	if (!GetWorld() || !GetWorld()->GetFirstPlayerController() || !GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()) return;

	const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();

	const auto Distance = FVector::Distance(PlayerLocation, GetActorLocation());

	HealthWidgetComponent->SetVisibility(Distance < HeathVisibilityDistance, true);
}