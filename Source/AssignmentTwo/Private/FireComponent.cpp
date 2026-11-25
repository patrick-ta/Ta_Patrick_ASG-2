#include "FireComponent.h"

#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"

UFireComponent::UFireComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UFireComponent::Fire()
{
	UWorld* World = GetWorld();
	AActor* Owner = GetOwner();
	if (!ProjectileClass || !World || !Owner)
	{
		return;
	}

	const float Now = World->GetTimeSeconds();
	if (Now - LastFireTime < FireCooldown)
	{
		return;
	}
	LastFireTime = Now;

	const FVector SpawnLocation = Owner->GetActorLocation() + Owner->GetActorForwardVector() * MuzzleOffset;
	const FRotator SpawnRotation = Owner->GetActorRotation();

	FActorSpawnParameters Params;
	Params.Owner = Owner;
	Params.Instigator = Cast<APawn>(Owner);
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	World->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, Params);
}