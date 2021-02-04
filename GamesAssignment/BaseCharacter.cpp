// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);
	ProjectileSpawnPoint->SetRelativeLocation(FVector(50.0f, 0.0f, 20.0f));*/
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Move"), this, &ABaseCharacter::MoveForwards);
	PlayerInputComponent->BindAxis(TEXT("Strafe"), this, &ABaseCharacter::Strafe);
	PlayerInputComponent->BindAxis(TEXT("Look Up"), this, &ABaseCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ABaseCharacter::Turn);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABaseCharacter::OnBeginFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ABaseCharacter::OnEndFire);
}

void ABaseCharacter::MoveForwards(float AxisAmount)
{
	AddMovementInput(GetActorForwardVector() * AxisAmount);
}

void ABaseCharacter::Strafe(float AxisAmount)
{
	AddMovementInput(GetActorRightVector() * AxisAmount);
}

void ABaseCharacter::LookUp(float AxisAmount)
{
	AddControllerPitchInput(AxisAmount);
}

void ABaseCharacter::Turn(float AxisAmount)
{
	AddControllerYawInput(AxisAmount);
}

void ABaseCharacter::OnBeginFire()
{

}

void ABaseCharacter::OnEndFire()
{
	//if (ProjectileClass)   //checks projectile has been set in blueprint editor
	//{
	//	FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
	//	FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
	//	AActor* TempProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation);
	//}

	AController* ControllerRef = GetController();
	FVector CameraLocation;
	FRotator CameraRotation;
	ControllerRef->GetPlayerViewPoint(CameraLocation, CameraRotation);   //sets the referance to the camera

	float CastRange = 10000.0f;
	FVector EndPoint = CameraLocation + CameraRotation.Vector() * CastRange;   //sets the end point relative to the camera rotation and location

	FHitResult Hit;
	bool bDidHit = GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, EndPoint, ECC_Visibility);

	UGameplayStatics::SpawnEmitterAttached(Particles, GetMesh(), TEXT("Muzzle_01"));   //creates a particle emitter at location of Muzzle_01 socket

	if (bDidHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *Hit.GetActor()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missed"));
	}
}