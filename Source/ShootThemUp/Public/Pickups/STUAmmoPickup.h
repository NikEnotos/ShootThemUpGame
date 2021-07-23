// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickup.h"
#include "STUAmmoPickup.generated.h"

class ASTU_Base_Weapon;

UCLASS()
class SHOOTTHEMUP_API ASTUAmmoPickup : public ASTUBasePickup
{
	GENERATED_BODY()

public:

	TSubclassOf<ASTU_Base_Weapon> GetWeaponType() { return WeaponType; }
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
		int32 ClipsAmount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		TSubclassOf<ASTU_Base_Weapon> WeaponType;


private:

	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
