// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STU_HealthComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTU_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTU_HealthComponent();

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;

	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable, Category = "Health")
		bool IsDead() const { return FMath::IsNearlyZero(Health); }

	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetHealthPercent()const { return Health / MaxHealth; }

protected:
	// Called when the game starts

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
		bool AutoHeal = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal", ClampMin = "0.0", ClampMax = "10.0"))
		float HealUpdateTime = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal", ClampMin = "0.0", ClampMax = "10.0"))
		float HealDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal", ClampMin = "0.0", ClampMax = "10.0"))
		float HealModifier = 1.0f;


	virtual void BeginPlay() override;



private:
	float Health = 0.0f;

	FTimerHandle HealUpdateTimer; //дескриптор таймера до востановления здоровья

	void HealUpdate();
	void SetHealth(float NewHealth);

	UFUNCTION()
	void OnTakeAnyDamage(
		AActor* DamageActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
