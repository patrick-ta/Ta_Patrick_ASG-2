#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AsgTwoGameMode.generated.h"

class UUserWidget;

UCLASS()
class ASSIGNMENTTWO_API AAsgTwoGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAsgTwoGameMode();

	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Points);

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> HealthWidgetClass;

private:
	int32 Score = 0;
};