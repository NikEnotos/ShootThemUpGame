// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STU_PlayerHUDWidget.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTU_PlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "UI")
		float GetHealthPersent() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
		bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
		bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
		bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
		bool IsPlayerSpectating() const; 

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
		void OnTakeDamage();

protected:

	virtual void NativeOnInitialized() override;

private:
	
	void OnHealthChanged(float Health, float HealthDelta);

	void OnNewPawn(APawn* NewPawn);
};
