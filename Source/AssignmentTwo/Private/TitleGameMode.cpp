#include "TitleGameMode.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

ATitleGameMode::ATitleGameMode()
{
	DefaultPawnClass = nullptr;
}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!TitleWidgetClass || !PC)
	{
		return;
	}

	if (UUserWidget* Widget = CreateWidget<UUserWidget>(PC, TitleWidgetClass))
	{
		Widget->AddToViewport();
	}

	PC->SetInputMode(FInputModeUIOnly());
	PC->SetShowMouseCursor(true);
}