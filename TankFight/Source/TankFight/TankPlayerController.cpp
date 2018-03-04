// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	ATank* PossesedTank = GetControlledTank();

	if (PossesedTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player Controlled tank is %s"), *PossesedTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("There is no player possessed tank"));
	}	
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("Aiming!"));
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) { return; }

	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation)) {
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *HitLocation.ToString());
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
	// Find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	// deproject screen position to a world direction
	// Line-trace along that direction and see what we hit (up to max range)
	return true;
}
