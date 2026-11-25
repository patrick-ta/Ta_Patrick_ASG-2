#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FireComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ASSIGNMENTTWO_API UFireComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFireComponent();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool Fire();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float FireCooldown = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float MuzzleOffset = 50.f;

private:
	float LastFireTime = -1000.f;
};