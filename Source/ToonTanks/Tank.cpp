// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));

    SpringArm->SetupAttachment(RootComponent);

    Camera->SetupAttachment(SpringArm);
}

void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(PlayerControllerRef)
    {
        FHitResult HitResult;
        PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
        //DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 30.f, 12, FColor::Red);
        RotateTurret(HitResult.ImpactPoint);
    }
}

void ATank::BeginPlay()
{
    Super::BeginPlay();
    
    PlayerControllerRef = Cast<APlayerController>(GetController());
}

void ATank::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);

    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}

void ATank::Move(float Value)
{
    FVector DeltaLocation = FVector::ZeroVector;

    DeltaLocation.X = Value * MoveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);

    AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;

    DeltaRotation.Yaw = Value * TurnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);

    AddActorLocalRotation(DeltaRotation, true);
}