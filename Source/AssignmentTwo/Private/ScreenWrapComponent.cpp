#include "ScreenWrapComponent.h"

#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"

UScreenWrapComponent::UScreenWrapComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

bool UScreenWrapComponent::GetViewBounds(const UObject* WorldContext, float PlaneY, FVector2D& OutMin, FVector2D& OutMax)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContext, 0);
	if (!PC || !PC->PlayerCameraManager)
	{
		return false;
	}

	int32 SizeX = 0;
	int32 SizeY = 0;
	PC->GetViewportSize(SizeX, SizeY);
	if (SizeX <= 0 || SizeY <= 0)
	{
		return false;
	}

	const FMinimalViewInfo View = PC->PlayerCameraManager->GetCameraCacheView();
	const float Aspect = View.bConstrainAspectRatio ? View.AspectRatio : static_cast<float>(SizeX) / SizeY;

	float HalfWidth = 0.f;
	if (View.ProjectionMode == ECameraProjectionMode::Orthographic)
	{
		HalfWidth = View.OrthoWidth * 0.5f;
	}
	else
	{
		HalfWidth = FMath::Tan(FMath::DegreesToRadians(View.FOV * 0.5f)) * FMath::Abs(PlaneY - View.Location.Y);
	}
	const float HalfHeight = HalfWidth / Aspect;

	OutMin = FVector2D(View.Location.X - HalfWidth, View.Location.Z - HalfHeight);
	OutMax = FVector2D(View.Location.X + HalfWidth, View.Location.Z + HalfHeight);
	return true;
}

void UScreenWrapComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Owner = GetOwner();
	const FVector Current = Owner->GetActorLocation();

	FVector2D Min;
	FVector2D Max;
	if (!GetViewBounds(this, Current.Y, Min, Max))
	{
		return;
	}

	const float MinX = Min.X - Margin;
	const float MaxX = Max.X + Margin;
	const float MinZ = Min.Y - Margin;
	const float MaxZ = Max.Y + Margin;

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