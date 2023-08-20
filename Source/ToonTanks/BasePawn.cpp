// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
//#include "DrawDebugHelpers.h"
#include "Bullet.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));

	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Project Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::RotateTurret(const FVector& LookAtTarget)
{
	FVector TargetVector = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator TargetRotation(0.f, TargetVector.Rotation().Yaw, 0.f);
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(TurretMesh->GetComponentRotation(), 
		TargetRotation, 
		UGameplayStatics::GetWorldDeltaSeconds(this), TurretRotationInterpSpeed)
		);
}

void ABasePawn::Fire()
{
	//DrawDebugSphere(GetWorld(), ProjectileSpawnPoint->GetComponentLocation(), 20.f, 12, FColor::Red, false, 3.f);
	auto Bullet = GetWorld()->SpawnActor<ABullet>(BulletClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
	Bullet->SetOwner(this);
}