// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STU_Weapon_Component.generated.h"

class ASTU_Base_Weapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTU_Weapon_Component : public UActorComponent
{
	GENERATED_BODY()

public:	

	USTU_Weapon_Component();

	virtual void StartFire();
	void StopFire();
	virtual void NextWeapon();
	void Reload();

	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	bool TryToAddAmmo(TSubclassOf<ASTU_Base_Weapon> WeaponType, int32 ClipsAmount);
	bool NeedAmmo(TSubclassOf<ASTU_Base_Weapon> WeaponType);

	bool GetWantToPickupWeapon() { return WantToPickupWeapon; }
	void SetWantToPickupWeapon(bool DoWants);

	void Zoom(bool Enabled);

	bool CharIsRuning = false;

	float GetCurrentBulletSpread();

	void SetCanPickup(bool IsCan) { CanPickup = IsCan; }
	bool GetCanPickup() { return CanPickup; }

	bool PickupWeapon(TSubclassOf<ASTU_Base_Weapon> PickupedWeapon, FAmmoData AmmoInPickupedWeapon);

	bool DropCurrentWeapon();

	//TArray<ASTU_Base_Weapon*> GetWeapons() { return Weapons; }

protected:

	bool CanPickup = false;

	//UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	//TArray<FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TArray<TSubclassOf<ASTU_Base_Weapon>> WeaponData;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* EquipAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Drop")
		float DropDistance = 400.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Drop")
		float TimeOfExistDroppedWeapon = 30.0f;

	UPROPERTY()
	ASTU_Base_Weapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASTU_Base_Weapon*> Weapons;

	int32 CurrentWeaponIndex = 0;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	bool CanFire() const;

	bool CanEquip() const;

	void EquipWeapon(int32 WeaponIndex);

private:

	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;

	bool EquipAnimInProgres = false;
	bool ReloadAnimInProgres = false;

	bool WantToPickupWeapon = false;

	void SpawnWeapons();

	void AttachWeaponToSocket(ASTU_Base_Weapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	void PlayAnimMontage(UAnimMontage* Animation);

	void InitAnimations();

	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	bool CanReload() const; 

	void OnClipEmpty(ASTU_Base_Weapon* AmmoEmptyWeapon);
	void ChangeClip();
};
