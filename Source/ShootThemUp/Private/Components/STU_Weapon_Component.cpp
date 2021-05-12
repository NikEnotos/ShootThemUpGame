// NikotiN Game Studio. All Rights Reserved 


#include "Components/STU_Weapon_Component.h"
#include "Weapon/STU_Base_Weapon.h"
#include "GameFramework/Character.h"
#include "Animation/STU_EquipFinishedAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

USTU_Weapon_Component::USTU_Weapon_Component()
{

	PrimaryComponentTick.bCanEverTick = false;

}


void USTU_Weapon_Component::BeginPlay()
{
	Super::BeginPlay();

	CurrentWeaponIndex = 0;
	InitAnimations();
	SpawnWeapons();
	
	EquipWeapon(CurrentWeaponIndex);
}

void USTU_Weapon_Component::EndPlay(const EEndPlayReason::Type EndPlayReason) 
{
	CurrentWeapon = nullptr;
	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);  
		Weapon->Destroy();
	}
	Weapons.Empty();
	Super::EndPlay(EndPlayReason);
}

void USTU_Weapon_Component::SpawnWeapons()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld()) return;

	for (auto OneWeaponData : WeaponData)
	{
		auto Weapon = GetWorld()->SpawnActor<ASTU_Base_Weapon>(OneWeaponData.WeaponClass);
		if (!Weapon) continue;

		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}

	
}

void USTU_Weapon_Component::AttachWeaponToSocket(ASTU_Base_Weapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
	if (!Weapon || !SceneComponent) return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void USTU_Weapon_Component::EquipWeapon(int32 WeaponIndex)
{
	if (WeaponIndex<0 || WeaponIndex>Weapons.Num())
	{
		UE_LOG(LogWeaponComponent, Warning, TEXT("Invalid Weapon Index!"));
		return;
	}

	ACharacter* Character = Cast<ACharacter>(GetOwner());

	if (!Character) return;

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];

	//CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage; // Not correct way
	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data) {		//
		return Data.WeaponClass == CurrentWeapon->GetClass();										//
	});

	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);

	EquipAnimInProgres = true;

	PlayAnimMontage(EquipAnimMontage);
}

void USTU_Weapon_Component::StartFire()
{
	
	if (!CanFire()) return;

	CurrentWeapon->StartFire();

}

void USTU_Weapon_Component::StopFire()
{

	if (!CurrentWeapon) return;

	CurrentWeapon->StopFire();

}

void USTU_Weapon_Component::NextWeapon()
{
	if (!CanEquip())return;

	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();    // 57 leason time: 10:12

	EquipWeapon(CurrentWeaponIndex);
}

void USTU_Weapon_Component::PlayAnimMontage(UAnimMontage* Animation)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());

	if (!Character) return;

	Character->PlayAnimMontage(Animation);
}

void USTU_Weapon_Component::InitAnimations()
{
	if (!EquipAnimMontage) return;
	const auto NotifyEvents = EquipAnimMontage->Notifies;

	for (auto NotifyEvent : NotifyEvents)
	{
		auto EquipFinishedNotify = Cast<USTU_EquipFinishedAnimNotify>(NotifyEvent.Notify);

		if (EquipFinishedNotify)
		{
			EquipFinishedNotify->OnNotified.AddUObject(this, &USTU_Weapon_Component::OnEquipFinished);  //Sign up for the delegate that activates when the triger in outfit animation is triggered
			break;
		}
	}

}

void USTU_Weapon_Component::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || Character->GetMesh() != MeshComponent) return;

	EquipAnimInProgres = false;

}

bool USTU_Weapon_Component::CanFire() const
{
	return CurrentWeapon && !EquipAnimInProgres;
}

bool USTU_Weapon_Component::CanEquip() const
{
	return !EquipAnimInProgres;
}

void USTU_Weapon_Component::Reload()
{
	PlayAnimMontage(CurrentReloadAnimMontage);
}
