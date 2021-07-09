// NikotiN Game Studio. All Rights Reserved 

#include "Weapon/Component/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "Sound/SoundCue.h"
//#include "PhysicalMaterials/PhysicalMaterial.h"


USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	auto ImpactData = DefaultImpactData;

	if (Hit.PhysMaterial.IsValid())
	{
		const auto PhysMat = Hit.PhysMaterial.Get();

		if (ImpactDataMap.Contains(PhysMat))
		{
			ImpactData = ImpactDataMap[PhysMat];
		}
	}

	// niagara spawn
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(				//
		GetWorld(),												//
		ImpactData.NiagareEffect,								//
		Hit.ImpactPoint,										//
		Hit.ImpactNormal.Rotation());

	// dical spawn
	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(						//
		GetWorld(),												//
		ImpactData.DecalData.Material,							//
		ImpactData.DecalData.Size,								//
		Hit.ImpactPoint,										//
		Hit.ImpactNormal.Rotation());
	
	if (DecalComponent)
	{
		DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
	}

	// sound
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactData.SoundOfImpact, Hit.ImpactPoint);
}