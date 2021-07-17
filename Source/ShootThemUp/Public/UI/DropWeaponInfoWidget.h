// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "DropWeaponInfoWidget.generated.h"

class UImage;

UCLASS()
class SHOOTTHEMUP_API UDropWeaponInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "UI")
		void SetDroppedWeaponUIData(FWeaponUIData UIData);

	UPROPERTY(meta = (BindWidget))
		UImage* DropWeaponImage;

};
