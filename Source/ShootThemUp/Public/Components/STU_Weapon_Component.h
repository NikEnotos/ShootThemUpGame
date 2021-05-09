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
	void NextWeapon();

protected:


	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<TSubclassOf<ASTU_Base_Weapon>> WeaponClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";


	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* EquipAnimMontage;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

	UPROPERTY()
	ASTU_Base_Weapon* CurrentWeapon = nullptr;

	UPROPERTY()
		TArray<ASTU_Base_Weapon*> Weapons;

	int32 CurrentWeaponIndex = 0;

	bool EquipAnimInProgres = false;

	void SpawnWeapons();

	void AttachWeaponToSocket(ASTU_Base_Weapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	void EquipWeapon(int32 WeaponIndex);

	void PlayAnimMontage(UAnimMontage* Animation);

	void InitAnimations();

	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);

	bool CanFire() const;

	bool CanEquip() const; 

};
