#include "HealthWidget.h"

#include "Components/Image.h"
#include "Engine/Texture2D.h"
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

	if (Health == DisplayedHealth)
	{
		return;
	}
	DisplayedHealth = Health;

	if (HealthTextures.IsValidIndex(Health) && HealthTextures[Health])
	{
		HealthImage->SetBrushFromTexture(HealthTextures[Health], true);
	}
}