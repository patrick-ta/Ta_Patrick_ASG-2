#include "ScreenWrapComponent.h"

#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"

UScreenWrapComponent::UScreenWrapComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UScreenWrapComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC || !PC->PlayerCameraManager)
	{
		return;
	}

	int32 SizeX = 0;
	int32 SizeY = 0;
	PC->GetViewportSize(SizeX, SizeY);
	if (SizeX <= 0 || SizeY <= 0)
	{
		return;
	}

	AActor* Owner = GetOwner();
	const FVector Current = Owner->GetActorLocation();
	const FMinimalViewInfo View = PC->PlayerCameraManager->GetCameraCacheView();

	const float Aspect = View.bConstrainAspectRatio ? View.AspectRatio : static_cast<float>(SizeX) / SizeY;

	float HalfWidth = 0.f;
	if (View.ProjectionMode == ECameraProjectionMode::Orthographic)
	{
		HalfWidth = View.OrthoWidth * 0.5f;
	}
	else
	{
		HalfWidth = FMath::Tan(FMath::DegreesToRadians(View.FOV * 0.5f)) * FMath::Abs(Current.Y - View.Location.Y);
	}
	const float HalfHeight = HalfWidth / Aspect;

	const float MinX = View.Location.X - HalfWidth - Margin;
	const float MaxX = View.Location.X + HalfWidth + Margin;
	const float MinZ = View.Location.Z - HalfHeight - Margin;
	const float MaxZ = View.Location.Z + HalfHeight + Margin;

	FVector Location = Current;

	if (Location.X > MaxX)
	{
		Location.X = MinX;
	}
	else if (Location.X < MinX)
	{
		Location.X = MaxX;
	}

	if (Location.Z > MaxZ)
	{
		Location.Z = MinZ;
	}
	else if (Location.Z < MinZ)
	{
		Location.Z = MaxZ;
	}

	if (!Location.Equals(Current))
	{
		Owner->SetActorLocation(Location, false, nullptr, ETeleportType::TeleportPhysics);
	}
}