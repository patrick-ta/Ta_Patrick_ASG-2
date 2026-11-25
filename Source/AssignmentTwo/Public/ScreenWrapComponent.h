#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScreenWrapComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ASSIGNMENTTWO_API UScreenWrapComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UScreenWrapComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wrap")
	float Margin = 50.f;
};