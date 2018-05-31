// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimBarrelAtCrosshair();
}

void ATankPlayerController::AimBarrelAtCrosshair()
{
	if (!GetControlledTank()) return;

	FVector OutHitLocation;
	if (GetSightRayHitLocation(OutHitLocation))
	{
		GetControlledTank()->AimAt(OutHitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation(CrossHairXLocation * ViewportSizeX, CrossHairYLocation * ViewportSizeY);

	FVector CameraWorldLocation, LookDirection;
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);

	FHitResult HitResult;

	bool hit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		PlayerCameraManager->GetCameraLocation(), 
		PlayerCameraManager->GetCameraLocation() + LookDirection * LineTraceRange,
		ECollisionChannel::ECC_Visibility
	);
	OutHitLocation = HitResult.Location;
	return hit;
}
