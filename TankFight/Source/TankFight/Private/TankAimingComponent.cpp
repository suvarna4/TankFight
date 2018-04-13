// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::Fire() {
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (AimingStatus != EAiming::Reloading && AimingStatus != EAiming::OutOfAmmo) {
		if (!ensure(Barrel && ProjectileBlueprint)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		Ammo -= 1;
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

EAiming UTankAimingComponent::GetAimingState() const {
	return AimingStatus;
}

void UTankAimingComponent::BeginPlay() {
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) {
	if (Ammo <= 0) {
		AimingStatus = EAiming::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) {
		AimingStatus = EAiming::Reloading;
	}
	else if (IsBarrelMoving()) {
		AimingStatus = EAiming::Loaded;
	}
	else {
		AimingStatus = EAiming::Locked;
	}
}

void UTankAimingComponent::AimAt(FVector HitLocation) {
	if (!ensure(Barrel || !Turret)) { return; }

	FVector LaunchVelocity;
	if (UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, Barrel->GetSocketLocation(FName("Projectile")), HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		AimDirection = LaunchVelocity.GetSafeNormal();
		
		MoveBarrel();
	}
}

void UTankAimingComponent::MoveBarrel() {
	if (!ensure(Barrel || Turret)) { return; }
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotation = AimRotator - BarrelRotation;

	Barrel->Elevate(DeltaRotation.Pitch);
	if (FMath::Abs(DeltaRotation.Yaw) < 180) {
		Turret->Rotate(DeltaRotation.Yaw);
	}
	else {
		Turret->Rotate(-DeltaRotation.Yaw);
	}
}

bool UTankAimingComponent::IsBarrelMoving() {
	return !Barrel->GetForwardVector().Equals(AimDirection, .01);
}



