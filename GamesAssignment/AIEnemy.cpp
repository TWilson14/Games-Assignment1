// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"

void AAIEnemy::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
	RandomPatrol();
}

AActor* AAIEnemy::ChooseWaypoint()
{
	int index = FMath::RandRange(0, Waypoints.Num() - 1);
	return Waypoints[index];
}

void AAIEnemy::RandomPatrol()
{
	MoveToActor(ChooseWaypoint());
}

void AAIEnemy::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	RandomPatrol();
}