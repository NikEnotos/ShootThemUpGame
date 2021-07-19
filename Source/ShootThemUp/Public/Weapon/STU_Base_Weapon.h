// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUCoreTypes.h"
#include "STU_Base_Weapon.generated.h"

class USkeletalMeshComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class USoundCue;

class USphereComponent;
class UWidgetComponent;

UCLASS()
class SHOOTTHEMUP_API ASTU_Base_Weapon : public AActor
{
	GENERATED_BODY()

public:

	ASTU_Base_Weapon();

	FOnClipEmptySignature OnClipEmpty;

	virtual void StartFire();
	virtual void StopFire();

	USkeletalMeshComponent* GetWeaponMesh() { return WeaponMesh; }

	virtual float GetCurrentBulletSpread() { return 0.0f; }

	TSubclassOf<ASTU_Base_Weapon> GetWeaponClass() { return GetClass(); }

	UAnimMontage* GetReloadAnimMontage() { return ReloadAnimMontage; }

	void SetSimulatePhysicsForDrop(bool IsSimulate);
	void SetCollisionForWeaponOnHand();

	void ChangeClip();
	bool CanReload() const;

	FWeaponUIData GetUIData() const { return UIData; }

	FAmmoData GetAmmoData() const { return CurrentAmmo; }
	void SetCurrentAmmoOnDrop(FAmmoData AmmoOnDrop) { CurrentAmmo = AmmoOnDrop; }

	bool TryToAddAmmo(int32 ClipsAmount);

	bool IsAmmoEmpty() const;

	bool ISAmmoFull() const;

	void InfoOnPickup(bool IsVisible);

	virtual void Zoom(bool Enabled) {}

	void IsPickupped(bool IsPiskupped);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, Category = "Pickup")
		USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "DropUI")
		UWidgetComponent* WeaponWidgetComponent;


	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		//USkeletalMesh* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		float TraceMaxDistance = 1500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		FAmmoData DefaultAmmo {15, 10, false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		UAnimMontage* ReloadAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		FWeaponUIData UIData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		UNiagaraSystem* MuzzleFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		USoundCue* FireSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		USoundCue* NoAmmoSound;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	virtual void BeginPlay() override;

	virtual void MakeShot();

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	FVector GetMuzzleWorldLocation() const;

	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	void DecreaseAmmo();

	bool IsClipEmpty() const;

	void LogAmmo();

	UNiagaraComponent* SpawnMuzzleFX();

private:

	FAmmoData CurrentAmmo;

};
