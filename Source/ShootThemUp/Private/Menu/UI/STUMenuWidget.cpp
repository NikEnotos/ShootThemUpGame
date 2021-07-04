// NikotiN Game Studio. All Rights Reserved 


#include "Menu/UI/STUMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STUGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameInstance, All, All);

void USTUMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnStartGame);
	}
}

void USTUMenuWidget::OnStartGame()
{
	if (!GetWorld()) return;
	
	const auto STUGameInstance = GetWorld()->GetGameInstance <USTUGameInstance>();
	if (!STUGameInstance) return;

	if (STUGameInstance->GetStartupLevelName().IsNone())
	{
		UE_LOG(LogGameInstance, Error, TEXT("Level name is NONE"));
		return;
	}


	UGameplayStatics::OpenLevel(this, STUGameInstance->GetStartupLevelName());
}