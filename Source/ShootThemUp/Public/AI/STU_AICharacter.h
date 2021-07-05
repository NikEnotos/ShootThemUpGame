// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "Player/STU_Character.h"
#include "STU_AICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class SHOOTTHEMUP_API ASTU_AICharacter : public ASTU_Character
{
	GENERATED_BODY()
	
public:

	ASTU_AICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		UBehaviorTree* BehaviorTreeAsset;

	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
		UWidgetComponent* HealthWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		float HeathVisibilityDistance = 1000.0f;

	//My 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		bool ShowHealthBar = true;

	virtual void BeginPlay() override;

	virtual void OnDeath() override;

	virtual void OnHelthChanged(float Health, float HealthDelta) override;

private:

	void UpdateHealthWidgetVisibility();

};
