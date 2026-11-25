#include "GameOverWidget.h"

#include "AsgTwoGameMode.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ReturnButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnReturnClicked);

	if (ScoreText)
	{
		if (const AAsgTwoGameMode* GameMode = GetWorld()->GetAuthGameMode<AAsgTwoGameMode>())
		{
			ScoreText->SetText(FText::FromString(FString::Printf(TEXT("FINAL SCORE: %d"), GameMode->GetScore())));
		}
	}
}

void UGameOverWidget::OnReturnClicked()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, TitleLevel);
}