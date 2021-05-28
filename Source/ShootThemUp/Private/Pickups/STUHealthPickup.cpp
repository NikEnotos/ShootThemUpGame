// NikotiN Game Studio. All Rights Reserved 


#include "Pickups/STUHealthPickup.h"
#include "Components/STU_HealthComponent.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool ASTUHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent <USTU_HealthComponent>(PlayerPawn);

	if (!HealthComponent || HealthComponent->IsDead()) return false;

	UE_LOG(LogHealthPickup, Display, TEXT("Health was taken"));

	return HealthComponent->TryToAddHealth(HealthAmount);
}