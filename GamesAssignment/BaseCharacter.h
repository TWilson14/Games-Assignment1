// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class GAMESASSIGNMENT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*UPROPERTY(EditAnywhere)
	USceneComponent* ProjectileSpawnPoint;*/

	/*UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;*/

	UPROPERTY(EditAnywhere)
	UParticleSystem* Particles;

private:
	void MoveForwards(float AxisAmount);
	void Strafe(float AxisAmount);
	void LookUp(float AxisAmount);
	void Turn(float AxisAmount);
	void OnBeginFire();
	void OnEndFire();
};