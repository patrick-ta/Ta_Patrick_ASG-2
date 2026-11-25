#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidget.generated.h"

class UImage;
class UTexture2D;

UCLASS()
class ASSIGNMENTTWO_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> HealthImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	TArray<TObjectPtr<UTexture2D>> HealthTextures;

private:
	int32 DisplayedHealth = -1;
};