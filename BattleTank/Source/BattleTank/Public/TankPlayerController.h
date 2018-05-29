// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5, CrossHairYLocation = 0.33333;

	ATank* GetControlledTank() const;
	void BeginPlay() override;
	void Tick( float DeltaTime) override;
	void AimBarrelAtCrosshair();
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;
};
