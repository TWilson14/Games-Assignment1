// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GAMESASSIGNMENT_API AAIEnemy : public AAIController
{
	GENERATED_BODY()


public:
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		TArray<AActor*> Waypoints;

	AActor* ChooseWaypoint();
	void RandomPatrol();
};
