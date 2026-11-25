#include "AsgTwoGameMode.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

AAsgTwoGameMode::AAsgTwoGameMode()
{
}

void AAsgTwoGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (!HealthWidgetClass)
	{
		return;
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (UUserWidget* Widget = CreateWidget<UUserWidget>(PC, HealthWidgetClass))
	{
		Widget->AddToViewport();
	}
}