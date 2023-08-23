// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::DestroyedActor(AActor* DestroyedActor)
{
    if (DestroyedActor == Tank)
    {
        Tank->HandleDestruction();
        if (ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }    
        
    }
    else if (ATower* DestroyedTower = Cast<ATower>(DestroyedActor))
    {
        DestroyedTower->HandleDestruction();
    }
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    
    StartGame();

    HandleStart();
}

void AToonTanksGameMode::HandleStart()
{
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    if (ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnabledState(false);

        FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController, 
            &AToonTanksPlayerController::SetPlayerEnabledState, 
            true
        );

        FTimerHandle TimerHandle;

        GetWorldTimerManager().SetTimer(
            TimerHandle, 
            TimerDelegate, 
            StartDelay, 
            false
        );
    }
}