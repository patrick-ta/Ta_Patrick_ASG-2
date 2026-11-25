#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

class UButton;
class UTextBlock;
class UWorld;

UCLASS()
class ASSIGNMENTTWO_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ReturnButton;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> ScoreText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameOver")
	TSoftObjectPtr<UWorld> TitleLevel;

private:
	UFUNCTION()
	void OnReturnClicked();
};