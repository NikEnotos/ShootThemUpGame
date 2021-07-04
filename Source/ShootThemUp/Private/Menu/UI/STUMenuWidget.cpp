// NikotiN Game Studio. All Rights Reserved 


#include "Menu/UI/STUMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "STUGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogMenuWidget, All, All);

void USTUMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnStartGame);
	}

	if (QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnQuitGame);
	}
}

void USTUMenuWidget::OnStartGame()
{
	if (!GetWorld()) return;
	
	const auto STUGameInstance = GetWorld()->GetGameInstance <USTUGameInstance>();
	if (!STUGameInstance) return;

	if (STUGameInstance->GetStartupLevelName().IsNone())
	{
		UE_LOG(LogMenuWidget, Error, TEXT("Level name is NONE"));
		return;
	}


	UGameplayStatics::OpenLevel(this, STUGameInstance->GetStartupLevelName());
}

void USTUMenuWidget::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}