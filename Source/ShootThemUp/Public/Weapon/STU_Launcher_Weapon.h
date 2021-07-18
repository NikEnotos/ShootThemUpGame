// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STU_Base_Weapon.h"
#include "STU_Launcher_Weapon.generated.h"


class ASTU_Projectile;
class USoundCue;

UCLASS()
class SHOOTTHEMUP_API ASTU_Launcher_Weapon : public ASTU_Base_Weapon
{
	GENERATED_BODY()
	
public:

	virtual void StartFire() override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<ASTU_Projectile> ProjectileClass;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	//	USoundCue* NoAmmoSound;

	virtual void MakeShot() override;



};
