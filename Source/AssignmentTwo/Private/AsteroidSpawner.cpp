#include "AsteroidSpawner.h"

#include "Asteroid.h"
#include "EngineUtils.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "ScreenWrapComponent.h"

AAsteroidSpawner::AAsteroidSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAsteroidSpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(InitialTimer, this, &AAsteroidSpawner::SpawnInitial, 0.5f, false);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AAsteroidSpawner::SpawnAsteroid, SpawnInterval, true);
}

void AAsteroidSpawner::SpawnInitial()
{
	for (int32 i = 0; i < InitialCount; ++i)
	{
		SpawnAsteroid();
	}
}

int32 AAsteroidSpawner::CountAsteroids() const
{
	int32 Count = 0;
	for (TActorIterator<AAsteroid> It(GetWorld()); It; ++It)
	{
		++Count;
	}
	return Count;
}

void AAsteroidSpawner::SpawnAsteroid()
{
	if (!AsteroidClass || CountAsteroids() >= MaxAsteroids)
	{
		return;
	}

	const float PlaneY = GetActorLocation().Y;

	FVector2D Min;
	FVector2D Max;
	if (!UScreenWrapComponent::GetViewBounds(this, PlaneY, Min, Max))
	{
		return;
	}

	Min.X -= SpawnMargin;
	Min.Y -= SpawnMargin;
	Max.X += SpawnMargin;
	Max.Y += SpawnMargin;

	FVector Location(0.f, PlaneY, 0.f);

	switch (FMath::RandRange(0, 3))
	{
	case 0:
		Location.X = Min.X;
		Location.Z = FMath::FRandRange(Min.Y, Max.Y);
		break;
	case 1:
		Location.X = Max.X;
		Location.Z = FMath::FRandRange(Min.Y, Max.Y);
		break;
	case 2:
		Location.Z = Min.Y;
		Location.X = FMath::FRandRange(Min.X, Max.X);
		break;
	default:
		Location.Z = Max.Y;
		Location.X = FMath::FRandRange(Min.X, Max.X);
		break;
	}

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AAsteroid* Asteroid = GetWorld()->SpawnActor<AAsteroid>(AsteroidClass, Location, FRotator::ZeroRotator, Params);
	if (Asteroid)
	{
		Asteroid->Setup(EAsteroidSize::Large);
	}
}