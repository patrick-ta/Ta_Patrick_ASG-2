#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Asteroid.generated.h"

class USphereComponent;
class UPaperFlipbookComponent;
class UScreenWrapComponent;

UENUM(BlueprintType)
enum class EAsteroidSize : uint8
{
	Large,
	Medium,
	Small
};

UCLASS()
class ASSIGNMENTTWO_API AAsteroid : public AActor
{
	GENERATED_BODY()

public:
	AAsteroid();

	virtual void Tick(float DeltaTime) override;

	void Setup(EAsteroidSize NewSize);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPaperFlipbookComponent> Flipbook;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UScreenWrapComponent> ScreenWrap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid")
	EAsteroidSize Size = EAsteroidSize::Large;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid")
	float LargeSpeed = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid")
	float MediumSpeed = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid")
	float SmallSpeed = 350.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid")
	float LargeScale = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid")
	float MediumScale = 0.6f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid")
	float SmallScale = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid")
	int32 LargePoints = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid")
	int32 MediumPoints = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid")
	int32 SmallPoints = 100;

private:
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Split();

	FVector Velocity = FVector::ZeroVector;
	bool bHit = false;
};