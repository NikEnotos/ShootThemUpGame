// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "UI/STUBaseWidget.h"
#include "STUCoreTypes.h"
#include "STU_PlayerHUDWidget.generated.h"

class UProgressBar;
class ASTU_Rifle_Weapon;

UCLASS()
class SHOOTTHEMUP_API USTU_PlayerHUDWidget : public USTUBaseWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		float GetCurrentBulletSpread();

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

	UFUNCTION(BlueprintCallable, Category = "UI")
		int32 GetKillsNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
		FString FormatBullets(int32 BulletsNum) const;

protected:

	UPROPERTY(meta = (BindWidget))
		UProgressBar* HealthProgressBar;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* DamageAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		float PercentColorThreshold = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		FLinearColor GoodColor = FLinearColor::White;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		FLinearColor BadColor = FLinearColor::Red;

	virtual void NativeOnInitialized() override;

private:

	UPROPERTY()
		ASTU_Rifle_Weapon* STU_Rifle_Weapon;
 	
	void OnHealthChanged(float Health, float HealthDelta);

	void OnNewPawn(APawn* NewPawn);

	void UpdateHealthBar();
};
