// NikotiN Game Studio. All Rights Reserved 


#include "UI/DropWeaponInfoWidget.h"
#include "Components/Image.h"

void UDropWeaponInfoWidget::SetDroppedWeaponUIData(FWeaponUIData UIData)
{
	DropWeaponImage->SetBrushFromTexture(UIData.MainIcon);
}