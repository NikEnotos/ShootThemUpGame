// NikotiN Game Studio. All Rights Reserved 

#pragma once

#include "CoreMinimal.h"
#include "Components/STU_Weapon_Component.h"
#include "STU_AIWeapon_Component.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTU_AIWeapon_Component : public USTU_Weapon_Component
{
	GENERATED_BODY()
	
public:

	virtual void StartFire() override;
	virtual void NextWeapon() override;

};
