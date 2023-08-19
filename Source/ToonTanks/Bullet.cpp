// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Bullet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));

	RootComponent = Bullet;

	ProjectileMovementComp = CreateAbstractDefaultSubobject<UProjectileMovementComponent>(TEXT("Porjectile Component"));

	ProjectileMovementComp->InitialSpeed = 1500.f;

	ProjectileMovementComp->MaxSpeed = 1500.f;

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

