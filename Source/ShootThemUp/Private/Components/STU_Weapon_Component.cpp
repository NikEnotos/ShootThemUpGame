// NikotiN Game Studio. All Rights Reserved 


#include "Components/STU_Weapon_Component.h"
#include "Weapon/STU_Base_Weapon.h"
#include "GameFramework/Character.h"
#include "Animation/STU_EquipFinishedAnimNotify.h"
#include "Animation/STU_ReloadAnimNotify.h"
#include "Animation/AnimUtils.h"
#include "Components/STU_HealthComponent.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

constexpr static int32 WeaponNum = 2;

USTU_Weapon_Component::USTU_Weapon_Component()
{

	PrimaryComponentTick.bCanEverTick = false;

}

void USTU_Weapon_Component::BeginPlay()
{
	Super::BeginPlay();

	checkf(WeaponData.Num() == WeaponNum, TEXT("Our character can hold only %i weapon items"), WeaponNum);

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

		Weapon->OnClipEmpty.AddUObject(this, &USTU_Weapon_Component::OnClipEmpty);

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
	auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<USTU_EquipFinishedAnimNotify>(EquipAnimMontage);
	if (EquipFinishedNotify)
	{
		EquipFinishedNotify->OnNotified.AddUObject(this, &USTU_Weapon_Component::OnEquipFinished);  //Sign up for the delegate that activates when the triger in outfit animation is triggered
	}
	else
	{
		UE_LOG(LogWeaponComponent, Error, TEXT("Equip anim notify is forgotten to set"));
		checkNoEntry();
	}

	for (auto OneWeaponData : WeaponData)
	{
		auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<USTU_ReloadAnimNotify>(OneWeaponData.ReloadAnimMontage);
		if (!ReloadFinishedNotify)
		{
			UE_LOG(LogWeaponComponent, Error, TEXT("Reload anim notify is forgotten to set"));
			checkNoEntry();
		}

		ReloadFinishedNotify->OnNotified.AddUObject(this, &USTU_Weapon_Component::OnReloadFinished);  //Sign up for the delegate that activates when the triger in outfit animation is triggered

	}
}

void USTU_Weapon_Component::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || Character->GetMesh() != MeshComponent) return;

	EquipAnimInProgres = false;

}

void USTU_Weapon_Component::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || Character->GetMesh() != MeshComponent) return;

	ReloadAnimInProgres = false;

}

bool USTU_Weapon_Component::CanFire() const
{
	return CurrentWeapon && !EquipAnimInProgres && !ReloadAnimInProgres && !CharIsRuning;
}

bool USTU_Weapon_Component::CanEquip() const
{
	const auto Pawn = GetOwner();
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTU_HealthComponent>(Pawn);

	return !EquipAnimInProgres && !ReloadAnimInProgres && !HealthComponent->IsDead();
}

bool USTU_Weapon_Component::CanReload() const
{
	return CurrentWeapon 
		&& !EquipAnimInProgres 
		&& !ReloadAnimInProgres
		&& CurrentWeapon->CanReload();
}

void USTU_Weapon_Component::Reload()
{
	ChangeClip();
}

void USTU_Weapon_Component::OnClipEmpty(ASTU_Base_Weapon* AmmoEmptyWeapon)
{
	if (!AmmoEmptyWeapon) return;
	if (CurrentWeapon == AmmoEmptyWeapon)
	{
		ChangeClip();
	}
	else
	{
		for (const auto Weapon : Weapons)
		{
			Weapon->ChangeClip();
		}
	}
}
void USTU_Weapon_Component::ChangeClip()
{
	if (!CanReload()) return;
	CurrentWeapon->StopFire();
	CurrentWeapon->ChangeClip();
	ReloadAnimInProgres = true;
	PlayAnimMontage(CurrentReloadAnimMontage);
}

bool USTU_Weapon_Component::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	if (CurrentWeapon)
	{
		UIData = CurrentWeapon->GetUIData();
		return true;
	}
	return false;
}

bool USTU_Weapon_Component::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	if (CurrentWeapon)
	{
		AmmoData = CurrentWeapon->GetAmmoData();
		return true;
	}
	return false;
}

bool USTU_Weapon_Component::TryToAddAmmo(TSubclassOf<ASTU_Base_Weapon> WeaponType, int32 ClipsAmount)
{
	for (const auto Weapon: Weapons)
	{
		if (Weapon && Weapon->IsA(WeaponType))
		{
			return Weapon->TryToAddAmmo(ClipsAmount);
		}
	}
	return false;
}

bool USTU_Weapon_Component::NeedAmmo(TSubclassOf<ASTU_Base_Weapon> WeaponType)
{
	for (const auto Weapon : Weapons)
	{
		if (Weapon && Weapon->IsA(WeaponType))
		{
			return !Weapon->ISAmmoFull();
		}
	}
	return false;
}