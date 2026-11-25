#include "TitleWidget.h"

#include "Components/Button.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UTitleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayButton->OnClicked.AddDynamic(this, &UTitleWidget::OnPlayClicked);

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UTitleWidget::OnQuitClicked);
	}
}

void UTitleWidget::OnPlayClicked()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, GameLevel);
}

void UTitleWidget::OnQuitClicked()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);
}