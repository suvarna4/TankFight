// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class TANKFIGHT_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	void BeginPlay() override;

private:
	void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = Aiming)
	float AcceptanceRadius = 8000;

};
