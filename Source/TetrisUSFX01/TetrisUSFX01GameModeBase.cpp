// Copyright Epic Games, Inc. All Rights Reserved.
#include "TetrisUSFX01GameModeBase.h"
#include "Board.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Engine/LevelStreaming.h"


ATetrisUSFX01GameModeBase::ATetrisUSFX01GameModeBase() {
    DefaultPawnClass = ABoard::StaticClass();
   

}

void ATetrisUSFX01GameModeBase::BeginPlay()
{
    //GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("Presione 1.PrimerNivel, 2.SegundoNivel 3.TercerNivel")));
    GetWorldTimerManager().SetTimer(crearBoard, this, &ATetrisUSFX01GameModeBase::crearNuevoBoard, 5.f, true);
    // Call the parent class version of this function
    Super::BeginPlay();

    for (TActorIterator<ACameraActor> it(GetWorld()); it; ++it)
    {
        UE_LOG(LogTemp, Warning, TEXT("Find camera: %s"), *(it->GetFName().ToString()));
        if (it->GetFName() == TEXT("BoardCamera"))
        {
            APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
            PC->SetViewTargetWithBlend(*it, 0.5);
            break;
        }
    }

}
void ATetrisUSFX01GameModeBase::crearNuevoBoard() {
    FString prueba = TEXT("prueba");  
    TArray<AActor*> Instances;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABoard::StaticClass(), Instances);//Obtenemos todos los catores de tipo board
    if (Instances.Num() >= 1) { // si ya hay almenos 1 (o mas boards) entonces no deja crear otro, pero caso contrario, SI crea un nuevo board.
        GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("Board Ya existe, no se puede crear otro."))); 
    }
    else {
        ABoard* boardNuevo = GetWorld()->SpawnActor<ABoard>(ABoard::StaticClass());
        GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("Creando nuevo board.")));
    }
    GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("%d Cantidad de boards: "), Instances.Num()));
    GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("Presione 1.PrimerNivel, 2.SegundoNivel 3.TercerNivel")));
 
}
