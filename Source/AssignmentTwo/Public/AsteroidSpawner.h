#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AsteroidSpawner.generated.h"

class AAsteroid;

UCLASS()
class ASSIGNMENTTWO_API AAsteroidSpawner : public AActor
{
	GENERATED_BODY()

public:
	AAsteroidSpawner();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TSubclassOf<AAsteroid> AsteroidClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	int32 InitialCount = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	int32 MaxAsteroids = 12;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float SpawnInterval = 4.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float SpawnMargin = 25.f;

private:
	void SpawnInitial();
	void SpawnAsteroid();
	int32 CountAsteroids() const;

	FTimerHandle InitialTimer;
	FTimerHandle SpawnTimer;
};