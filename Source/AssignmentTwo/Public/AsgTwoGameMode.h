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

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> HealthWidgetClass;
};