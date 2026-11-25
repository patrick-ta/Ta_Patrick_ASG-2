#include "PlayerCharacter.h"
#include "FireComponent.h"
#include "HealthComponent.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	UCharacterMovementComponent* Move = GetCharacterMovement();
	Move->GravityScale = 0.f;
	Move->BrakingDecelerationFlying = 0.f;
	Move->bConstrainToPlane = true;
	Move->SetPlaneConstraintNormal(FVector(0.f, 1.f, 0.f));
	Move->bSnapToPlaneAtStart = true;

	FireComponent = CreateDefaultSubobject<UFireComponent>(TEXT("FireComponent"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->SetMovementMode(MOVE_Flying);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (ULocalPlayer* LP = PC->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				Subsystem->AddMappingContext(MappingContext, 0);
			}
		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(RotateAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Rotate);
		EIC->BindAction(ThrustAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Thrust);
		EIC->BindAction(ThrustAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopThrust);
		EIC->BindAction(FireAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Fire);
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FireAnimTimeRemaining = FMath::Max(0.f, FireAnimTimeRemaining - DeltaTime);

	UPaperFlipbook* Desired = IdleFlipbook;
	if (HealthComponent->IsInvulnerable())
	{
		Desired = HurtFlipbook;
	}
	else if (FireAnimTimeRemaining > 0.f)
	{
		Desired = FireFlipbook;
	}
	else if (bThrusting)
	{
		Desired = ThrustFlipbook;
	}

	if (!Desired)
	{
		Desired = IdleFlipbook;
	}

	if (Desired && GetSprite()->GetFlipbook() != Desired)
	{
		GetSprite()->SetFlipbook(Desired);
	}
}

void APlayerCharacter::Rotate(const FInputActionValue& Value)
{
	ShipAngle = FMath::UnwindDegrees(ShipAngle + Value.Get<float>() * RotationSpeed * GetWorld()->GetDeltaSeconds());
	SetActorRotation(FRotator(ShipAngle, 0.f, 0.f));
}

void APlayerCharacter::Thrust(const FInputActionValue& Value)
{
	bThrusting = true;
	AddMovementInput(GetActorForwardVector(), 1.f);
}

void APlayerCharacter::StopThrust(const FInputActionValue& Value)
{
	bThrusting = false;
}

void APlayerCharacter::Fire(const FInputActionValue& Value)
{
	if (HealthComponent->IsInvulnerable())
	{
		return;
	}

	if (FireComponent->Fire())
	{
		FireAnimTimeRemaining = FireAnimDuration;
	}
}