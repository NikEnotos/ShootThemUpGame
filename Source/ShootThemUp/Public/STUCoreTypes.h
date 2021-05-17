#pragma once

#include "STUCoreTypes.generated.h"

//WEAPON

class ASTU_Base_Weapon;

DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature);

USTRUCT(BlueprintType)
struct FAmmoData
{

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinet"))
		int32 Clips;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		bool Infinet;
};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<ASTU_Base_Weapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		UAnimMontage* ReloadAnimMontage;
};

USTRUCT(BlueprintType)
struct FweaponUIData
{

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		UTexture2D* MainIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		UTexture2D* CrossHairIcon;
};

//HEALTH

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);
