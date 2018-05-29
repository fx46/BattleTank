// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tankou"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing: %s"), *(ControlledTank->GetName()));
	}
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
		//UE_LOG(LogTemp, Warning, TEXT("OutHitLocation: %s"), *OutHitLocation.ToString());
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Found no OutHitLocation"));
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	FVector WorldLocation, WorldDirection;

	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation(CrossHairXLocation*ViewportSizeX, CrossHairXLocation*ViewportSizeY);
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("WorldDirection: %s"), *WorldDirection.ToString());
	}

	//TODO: determine hit location and put it in OutHitLocation
	//TODO: return true if raycast hit something
	return true;
}
