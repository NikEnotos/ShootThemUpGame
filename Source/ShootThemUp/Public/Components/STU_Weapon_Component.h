// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STU_Weapon_Component.generated.h"

class ASTU_Base_Weapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTU_Weapon_Component : public UActorComponent
{
	GENERATED_BODY()

public:	

	USTU_Weapon_Component();

	void StartFire();
	void StopFire();

protected:


	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASTU_Base_Weapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponAttachPointName = "WeaponSocket";

	virtual void BeginPlay() override;

private:

	UPROPERTY()
	ASTU_Base_Weapon* CurrentWeapon = nullptr;

	void SpawnWeapon();

};
