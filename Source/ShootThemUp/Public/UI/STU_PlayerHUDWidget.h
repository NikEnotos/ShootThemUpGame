// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STU_PlayerHUDWidget.generated.h"

class USTU_Weapon_Component;

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

private:

	USTU_Weapon_Component* GetWeaponCoponent() const;
};
