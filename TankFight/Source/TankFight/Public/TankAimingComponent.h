// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;

UENUM()
enum class EAiming : uint8 {
	Locked,
	Loaded,
	Reloading,
	OutOfAmmo
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKFIGHT_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = InputEvent)
	void Fire();

	EAiming GetAimingState() const;

private:
	void BeginPlay() override;

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UTankBarrel * Barrel = nullptr;

	UTankTurret * Turret = nullptr;

	FVector AimDirection;

	void MoveBarrel();

	bool IsBarrelMoving();

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	EAiming AimingStatus = EAiming::Loaded;

	UPROPERTY(BlueprintReadOnly, Category = State)
	int Ammo = 10;
	
};
