#include "Asteroid.h"

#include "PaperFlipbookComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "HealthComponent.h"
#include "PlayerCharacter.h"
#include "ScreenWrapComponent.h"

AAsteroid::AAsteroid()
{
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->InitSphereRadius(50.f);
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Collision->SetGenerateOverlapEvents(true);
	SetRootComponent(Collision);

	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	Flipbook->SetupAttachment(Collision);
	Flipbook->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ScreenWrap = CreateDefaultSubobject<UScreenWrapComponent>(TEXT("ScreenWrap"));
}

void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AAsteroid::OnOverlap);
	Flipbook->SetRelativeLocation(FVector(0.f, FMath::FRandRange(0.f, 5.f), 0.f));
}

void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(Velocity * DeltaTime);
}

void AAsteroid::Setup(EAsteroidSize NewSize)
{
	Size = NewSize;

	float Speed = LargeSpeed;
	float Scale = LargeScale;

	if (Size == EAsteroidSize::Medium)
	{
		Speed = MediumSpeed;
		Scale = MediumScale;
	}
	else if (Size == EAsteroidSize::Small)
	{
		Speed = SmallSpeed;
		Scale = SmallScale;
	}

	SetActorScale3D(FVector(Scale));

	const float Angle = FMath::DegreesToRadians(FMath::FRandRange(0.f, 360.f));
	Velocity = FVector(FMath::Cos(Angle), 0.f, FMath::Sin(Angle)) * Speed;
}

void AAsteroid::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bHit || !OtherActor)
	{
		return;
	}

	if (UHealthComponent* Health = OtherActor->FindComponentByClass<UHealthComponent>())
	{
		Health->ApplyDamage(1);
		return;
	}

	if (!Cast<APlayerCharacter>(OtherActor->GetOwner()))
	{
		return;
	}

	bHit = true;
	OtherActor->Destroy();
	Split();
	Destroy();
}

void AAsteroid::Split()
{
	EAsteroidSize ChildSize;

	if (Size == EAsteroidSize::Large)
	{
		ChildSize = EAsteroidSize::Medium;
	}
	else if (Size == EAsteroidSize::Medium)
	{
		ChildSize = EAsteroidSize::Small;
	}
	else
	{
		return;
	}

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (int32 i = 0; i < 2; ++i)
	{
		AAsteroid* Child = GetWorld()->SpawnActor<AAsteroid>(GetClass(), GetActorLocation(), FRotator::ZeroRotator, Params);
		if (Child)
		{
			Child->Setup(ChildSize);
		}
	}
}