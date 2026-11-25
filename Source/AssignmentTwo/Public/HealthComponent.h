#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class UPaperFlipbookComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ASSIGNMENTTWO_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void ApplyDamage(int32 Amount);

	UFUNCTION(BlueprintPure, Category = "Health")
	bool IsInvulnerable() const;

	UFUNCTION(BlueprintPure, Category = "Health")
	int32 GetCurrentHealth() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 MaxHealth = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float InvulnerabilityDuration = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float FlickerInterval = 0.1f;

private:
	void SetTint(bool bTinted);

	UPROPERTY()
	TObjectPtr<UPaperFlipbookComponent> Sprite;

	int32 CurrentHealth = 0;
	float InvulnerableTimeRemaining = 0.f;
	float FlickerTimer = 0.f;
	bool bTintedRed = false;
};