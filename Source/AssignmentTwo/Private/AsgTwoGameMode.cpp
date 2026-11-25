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

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (PC)
	{
		// Reset input mode back to game — the title screen sets UIOnly + mouse cursor,
		// and those settings persist on the PlayerController across a level transition.
		PC->SetInputMode(FInputModeGameOnly());
		PC->SetShowMouseCursor(false);

		if (HealthWidgetClass)
		{
			if (UUserWidget* Widget = CreateWidget<UUserWidget>(PC, HealthWidgetClass))
			{
				Widget->AddToViewport();
			}
		}
	}
}

void AAsgTwoGameMode::AddScore(int32 Points)
{
	Score += Points;
}

int32 AAsgTwoGameMode::GetScore() const
{
	return Score;
}