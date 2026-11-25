#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

class UInputAction;
class UInputMappingContext;
class UFireComponent;
class UHealthComponent;

UCLASS()
class APlayerCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> RotateAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> ThrustAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RotationSpeed = 220.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<UFireComponent> FireComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	TObjectPtr<UHealthComponent> HealthComponent;

private:
	void Rotate(const FInputActionValue& Value);
	void Thrust(const FInputActionValue& Value);
	void Fire(const FInputActionValue& Value);

	float ShipAngle = 0.f;
};