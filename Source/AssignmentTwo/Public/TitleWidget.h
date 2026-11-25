#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidget.generated.h"

class UButton;
class UWorld;

UCLASS()
class ASSIGNMENTTWO_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> PlayButton;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UButton> QuitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Title")
	TSoftObjectPtr<UWorld> GameLevel;

private:
	UFUNCTION()
	void OnPlayClicked();

	UFUNCTION()
	void OnQuitClicked();
};