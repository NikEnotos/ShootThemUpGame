// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STU_Character.generated.h"

class USTU_HealthComponent;
class USTU_Weapon_Component;

UCLASS()
class SHOOTTHEMUP_API ASTU_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTU_Character(const FObjectInitializer& ObjInit);

protected:

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
		USTU_HealthComponent* HealthComponent;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
		USTU_Weapon_Component* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		float LifeSpanOnDeath = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		FVector2D LandedDamageVelocity = FVector2D(800.0f, 1200.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		FVector2D LandedDamage = FVector2D(5.0f, 100.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Material")
		FName MaterialColorName = "Paint Color";

	virtual void BeginPlay() override;

	virtual void OnDeath();

public:	

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		virtual bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		float GetMovementDirection() const;

	void SetPlayerColor(const FLinearColor& Color);

private:

	void OnHelthChanged(float Health, float HealthDelta);

	UFUNCTION()
		void OnGroundLanded(const FHitResult& Hit);

};
