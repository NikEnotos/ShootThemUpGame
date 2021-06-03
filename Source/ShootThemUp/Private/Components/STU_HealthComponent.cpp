// NikotiN Game Studio. All Rights Reserved 


#include "Components/STU_HealthComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Camera/CameraShake.h"

USTU_HealthComponent::USTU_HealthComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void USTU_HealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	check(MaxHealth > 0);

	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTU_HealthComponent::OnTakeAnyDamage);
	}

}

void USTU_HealthComponent::OnTakeAnyDamage(
	AActor* DamageActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{

	if (Damage <= 0.0f || IsDead() || !GetWorld()) return;

	SetHealth(Health - Damage);

	GetWorld()->GetTimerManager().ClearTimer(HealUpdateTimer);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}

	else if (AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealUpdateTimer, this, &USTU_HealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
	}

	PlayCameraShake();
}

void USTU_HealthComponent::HealUpdate()
{
	SetHealth(Health + HealModifier);

	if (FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealUpdateTimer);
	}
}

void USTU_HealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}

bool USTU_HealthComponent::TryToAddHealth(float HealthAmount)
{
	if (IsDead() || ISHealthFull()) return false;

	SetHealth(Health + HealthAmount);
	return true;
}

bool USTU_HealthComponent::ISHealthFull() const
{
	return FMath::IsNearlyEqual(Health, MaxHealth);
}

void USTU_HealthComponent::PlayCameraShake()
{
	if (IsDead()) return;


	const auto Player = Cast<APawn>(GetOwner());
	if (!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if (!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(CameraShake);

}




