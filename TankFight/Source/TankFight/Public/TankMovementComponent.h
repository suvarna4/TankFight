// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKFIGHT_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	// TODO check best protection
	
private:
	UTankTrack * LeftTrack = nullptr;
	UTankTrack * RightTrack = nullptr;

	void RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed);
	
};
