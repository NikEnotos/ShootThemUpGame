// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STU_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USTU_HealthComponent;
class UTextRenderComponent;

UCLASS()
class SHOOTTHEMUP_API ASTU_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTU_Character(const FObjectInitializer& ObjInit);

protected:
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
		UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
		USTU_HealthComponent* HealthComponent;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
		UTextRenderComponent* HealthTextComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		FVector2D LandedDamageVelocity = FVector2D(800.0f, 1200.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		FVector2D LandedDamage = FVector2D(5.0f, 100.0f);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		float GetMovementDirection() const;

private:
	bool WantsToRun = false;
	bool IsMovingForward = false;

	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void OnStartRunning();
	void OnStopRunning();

	void OnDeath();
	void OnHelthChanged(float Health);

	UFUNCTION()
		void OnGroundLanded(const FHitResult& Hit);
};
