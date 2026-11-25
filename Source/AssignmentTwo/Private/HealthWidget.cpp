#include "HealthWidget.h"

#include "AsgTwoGameMode.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "HealthComponent.h"

void UHealthWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	int32 Health = 0;
	if (APawn* Pawn = GetOwningPlayerPawn())
	{
		if (UHealthComponent* HealthComponent = Pawn->FindComponentByClass<UHealthComponent>())
		{
			Health = HealthComponent->GetCurrentHealth();
		}
	}

	if (Health != DisplayedHealth)
	{
		DisplayedHealth = Health;

		if (HealthTextures.IsValidIndex(Health) && HealthTextures[Health])
		{
			HealthImage->SetBrushFromTexture(HealthTextures[Health], true);
		}
	}

	if (ScoreText)
	{
		if (const AAsgTwoGameMode* GameMode = GetWorld()->GetAuthGameMode<AAsgTwoGameMode>())
		{
			const int32 Score = GameMode->GetScore();
			if (Score != DisplayedScore)
			{
				DisplayedScore = Score;
				ScoreText->SetText(FText::FromString(FString::Printf(TEXT("SCORE: %d"), Score)));
			}
		}
	}
}