// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STU_Base_Weapon.h"
#include "STU_Rifle_Weapon.generated.h"

class USTUWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;
//class UAudioComponent;
class UCameraShakeBase;

class USoundCue;

UCLASS()
class SHOOTTHEMUP_API ASTU_Rifle_Weapon : public ASTU_Base_Weapon
{
	GENERATED_BODY()
	
public:

	ASTU_Rifle_Weapon();

	virtual void StartFire() override;
	virtual void StopFire() override;

	virtual void Zoom(bool Enabled) override;

	virtual float GetCurrentBulletSpread() override { return CurrentBulletSpread; }

	virtual void MakeSingleShot() override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		float TimerBetweenShots = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		float ShotDistance = 2500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		float BulletSpread = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		float AddToBulletSpreadOnShot = 0.05f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		float DamageAmount = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		float FeeidOfViewZoomAngle = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		UNiagaraSystem* TraceFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		TSubclassOf<UCameraShakeBase> CameraShakeOnShot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		FString TraceTargetName = "TraceTarget";

	UPROPERTY(VisibleAnywhere, Category = "VFX")
		USTUWeaponFXComponent* WeaponFXComponent;

	virtual void BeginPlay() override;

	virtual void MakeShot() override;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;


private:
	FTimerHandle ShotTimerHandle;

	UPROPERTY()
		UNiagaraComponent* MuzzleFXComponent;

	//UPROPERTY()
		//UAudioComponent* FireAudioComponent;


	void MakeDamage(const FHitResult& HitResult);

	void InitFX();
	void SetFXActive(bool IsActive);

	void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);

	AController* GetController() const;

	void PlayCameraShakeOnShot() const;

	float DefaultCameraFOV = 90.0f;

	float CurrentBulletSpread;
};


