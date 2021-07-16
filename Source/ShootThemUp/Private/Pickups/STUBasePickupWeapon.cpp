// NikotiN Game Studio. All Rights Reserved 


#include "Pickups/STUBasePickupWeapon.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

#include "STUCoreTypes.h"
#include "STU_Base_Weapon.h"
#include "Components/SkeletalMeshComponent.h"

ASTUBasePickupWeapon::ASTUBasePickupWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

}

void  ASTUBasePickupWeapon::SetPickupData(FWeaponData WeaponData, FAmmoData CurrentWeaponAmmo, float TimeOfExistAfterDrop)
{

	
}

void ASTUBasePickupWeapon::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);


}

void ASTUBasePickupWeapon::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);


}

void ASTUBasePickupWeapon::PickupWasTaken()
{

}