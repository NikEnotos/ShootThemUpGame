 // NikotiN Game Studio. All Rights Reserved 


#include "Animation/STU_EquipFinishedAnimNotify.h"

void USTU_EquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}