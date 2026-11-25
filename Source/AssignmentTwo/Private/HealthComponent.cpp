#include "HealthComponent.h"

#include "AsgTwoGameMode.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "PaperFlipbookComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	Sprite = GetOwner()->FindComponentByClass<UPaperFlipbookComponent>();
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (InvulnerableTimeRemaining <= 0.f)
	{
		return;
	}

	InvulnerableTimeRemaining -= DeltaTime;
	FlickerTimer += DeltaTime;

	if (InvulnerableTimeRemaining <= 0.f)
	{
		InvulnerableTimeRemaining = 0.f;
		bTintedRed = false;
		SetTint(false);
		return;
	}

	if (FlickerTimer >= FlickerInterval)
	{
		FlickerTimer = 0.f;
		bTintedRed = !bTintedRed;
		SetTint(bTintedRed);
	}
}

void UHealthComponent::ApplyDamage(int32 Amount)
{
	if (IsInvulnerable() || CurrentHealth <= 0)
	{
		return;
	}

	CurrentHealth = FMath::Max(0, CurrentHealth - Amount);

	if (CurrentHealth <= 0)
	{
		if (AAsgTwoGameMode* GameMode = GetWorld()->GetAuthGameMode<AAsgTwoGameMode>())
		{
			GameMode->GameOver();
		}

		GetOwner()->Destroy();
		return;
	}

	InvulnerableTimeRemaining = InvulnerabilityDuration;
	FlickerTimer = 0.f;
	bTintedRed = true;
	SetTint(true);
}

bool UHealthComponent::IsInvulnerable() const
{
	return InvulnerableTimeRemaining > 0.f;
}

int32 UHealthComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}

void UHealthComponent::SetTint(bool bTinted)
{
	if (Sprite)
	{
		Sprite->SetSpriteColor(bTinted ? FLinearColor::Red : FLinearColor::White);
	}
}