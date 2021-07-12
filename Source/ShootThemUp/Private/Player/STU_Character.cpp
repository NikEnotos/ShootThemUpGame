// NikotiN Game Studio. All Rights Reserved 


#include "Player/STU_Character.h"
#include "Components/STU_CharacterMovementComponent.h"
#include "Components/STU_HealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/STU_Weapon_Component.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ASTU_Character::ASTU_Character(const FObjectInitializer& ObjInit) : Super(ObjInit.SetDefaultSubobjectClass<USTU_CharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<USTU_HealthComponent>("HealthComponent");

	WeaponComponent = CreateDefaultSubobject<USTU_Weapon_Component>("WeaponComponent");

}

// Called when the game starts or when spawned
void ASTU_Character::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(GetCharacterMovement());
	check(GetMesh());

	OnHelthChanged(HealthComponent->GetHealth(), 0.0f);
	HealthComponent->OnDeath.AddUObject(this, &ASTU_Character::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ASTU_Character::OnHelthChanged);

	LandedDelegate.AddDynamic(this, &ASTU_Character::OnGroundLanded);

}

void ASTU_Character::OnHelthChanged(float Health, float HealthDelta)
{
	
}

// Called every frame
void ASTU_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASTU_Character::IsRunning() const
{
	return false; // WantsToRun&& IsMovingForward && !GetVelocity().IsZero();
}

float  ASTU_Character::GetMovementDirection() const
{
	if (GetVelocity().IsZero()) return 0.0f;

	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	//return FMath::RadiansToDegrees(AngleBetween) * FMath::Sign(CrossProduct.Z); 
	return FMath::IsNearlyZero(CrossProduct.Size()) ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ASTU_Character::OnDeath()
{
	WeaponComponent->StopFire();

	WeaponComponent->Zoom(false);

	//PlayAnimMontage(DeathAnimMontage);

	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(LifeSpanOnDeath); //Destroy Actor in 5 sec
	
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
}

void ASTU_Character::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetCharacterMovement()->Velocity.Z;

	if (FallVelocityZ < LandedDamageVelocity.X) return;

	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);

	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}

void ASTU_Character::SetPlayerColor(const FLinearColor& Color)
{
	const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
	if (!MaterialInst) return;

	MaterialInst->SetVectorParameterValue(MaterialColorName, Color);

}

