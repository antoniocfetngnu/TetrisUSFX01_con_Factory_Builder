// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "DirectorPiezas.h"
#include "PiezaCruz.h"
#include "PiezaDispersa.h"
#include "PiezaTetramino.h"
#include "PiezaLineaPunteada.h"
#include "Pieza3Bloques.h"
#include "Pieza.h"

#include "Kismet/GameplayStatics.h"
// Sets default values

ABoard::ABoard()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
    /*CurrentPiece->puntuacion = 0;*/
    PiezaCruzBuilder = GetWorld()->SpawnActor<APiezaCruz>(APiezaCruz::StaticClass());
    PiezaDispersaBuilder = GetWorld()->SpawnActor<APiezaDispersa>(APiezaDispersa::StaticClass());
    PiezaTetraminoBuilder = GetWorld()->SpawnActor<APiezaTetramino>(APiezaTetramino::StaticClass()); 
    PiezaLineaPunteadaBuilder = GetWorld()->SpawnActor<APiezaLineaPunteada>(APiezaLineaPunteada::StaticClass());
    Pieza3BloquesBuilder = GetWorld()->SpawnActor<APieza3Bloques>(APieza3Bloques::StaticClass());
    Director = GetWorld()->SpawnActor<ADirectorPiezas>(ADirectorPiezas::StaticClass());
    //CREACION DE FACTORY DE NIVELES
    FabricaEscenas = GetWorld()->SpawnActor<AFactoryNivelesConcreta>(AFactoryNivelesConcreta::StaticClass());
    
    for (TActorIterator<APieza> it(GetWorld()); it; ++it)
    {
        
        if (it->GetFName() == TEXT("DissmissPieces"))
        {
            it->Dismiss();
            it->Destroy();
        }
    }
}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (bGameOver)
    {
        return;
    }

    switch (Status)
    {
    case PS_NOT_INITED:
        NewPiece();
        CoolLeft = CoolDown;
        Status = PS_MOVING;
        break;
    case PS_MOVING:
        CoolLeft -= DeltaTime;
        if (CoolLeft <= 0.0f)
        {
            MoveDown();
        }
        break;
    case PS_GOT_BOTTOM:
        CoolLeft -= DeltaTime;
        if (CoolLeft <= 0.0f)
        {
            if (CurrentPiece)
            {
                CurrentPiece->Dismiss();
                CurrentPiece->Destroy();
            }
            CurrentPiece = nullptr;
            NewPiece();
            CoolLeft = CoolDown;
            Status = PS_MOVING;
        }
        break;
    default:
        break;
    }
}

// Called to bind functionality to input
void ABoard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction("Rotate", IE_Pressed, this, &ABoard::Rotate);
    PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &ABoard::MoveLeft);
    PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &ABoard::MoveRight);
    PlayerInputComponent->BindAction("MoveDownToEnd", IE_Pressed, this, &ABoard::MoveDownToEnd);
    PlayerInputComponent->BindAction("CambiarNivel1", IE_Pressed, this, &ABoard::CambiarNivel1);
    PlayerInputComponent->BindAction("CambiarNivel2", IE_Pressed, this, &ABoard::CambiarNivel2);
    PlayerInputComponent->BindAction("CambiarNivel3", IE_Pressed, this, &ABoard::CambiarNivel3);
    /*PlayerInputComponent->BindAction("CambiarNivel3", IE_Pressed, this, &ABoard::CambiarNivel1);*/
  

}
void ABoard::CambiarNivel1() {
    FabricaEscenas->cargarNivel("MapaTetris");
}
void ABoard::CambiarNivel2() {
    FabricaEscenas->cargarNivel("MapaTetris2");
}
void ABoard::CambiarNivel3() {
    FabricaEscenas->cargarNivel("MapaTetris3");
}

void ABoard::Rotate()
{
    if (CurrentPiece && Status != PS_GOT_BOTTOM)
    {
        CurrentPiece->TestRotate();
    }
}


void ABoard::MoveLeft()
{
    if (CurrentPiece)
    {
        CurrentPiece->MoveLeft();
        if (Status == PS_GOT_BOTTOM)
        {
            MoveDownToEnd();
        }
    }
}

void ABoard::MoveRight()
{
    if (CurrentPiece)
    {
        CurrentPiece->MoveRight();
        if (Status == PS_GOT_BOTTOM)
        {
            MoveDownToEnd();
        }
    }
}

void ABoard::MoveDown()
{
    if (CurrentPiece)
    {
        if (!CurrentPiece->MoveDown())
        {
            Status = PS_GOT_BOTTOM;
        }
        CoolLeft = CoolDown;
    }
}

void ABoard::NewPiece()
{
    CheckLine();
    UE_LOG(LogTemp, Warning, TEXT("GENERANDO NUEVA PIEZA!"));
    if (CurrentPiece)
    {
        UE_LOG(LogTemp, Warning, TEXT("SI HAY CURRENT PIECE, ELIMINANDOOOO!"));
        CurrentPiece->Dismiss();
        CurrentPiece->Destroy();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("NO HAY CURRENT PIECE!!!!"));
    }
    int selectorBuilders = FMath::RandRange(0, 7);
    switch (selectorBuilders)
    {
    case 0:
    case 1:
    case 2:
        Director->AsignarConstructorDePieza(PiezaTetraminoBuilder);
        break;
    case 3:
    case 4:
        Director->AsignarConstructorDePieza(Pieza3BloquesBuilder);
        break;
    case 5:
        Director->AsignarConstructorDePieza(PiezaLineaPunteadaBuilder);
        break;
    case 6:
        Director->AsignarConstructorDePieza(PiezaCruzBuilder);
        break;
    case 7:
        Director->AsignarConstructorDePieza(PiezaDispersaBuilder);
        break;
    default:
        Director->AsignarConstructorDePieza(PiezaCruzBuilder);
        break;
    }
    //PiezaCruzBuilder = GetWorld()->SpawnActor<APiezaCruz>(APiezaCruz::StaticClass());
    /*Director = GetWorld()->SpawnActor<ADirectorPiezas>(ADirectorPiezas::StaticClass());*/
    /*Director->AsignarConstructorDePieza(PiezaCruzBuilder);*/
    Director->ConstruirPieza();
    //APieza* PiezaGenerada = Director->GetPieza();
    CurrentPiece = Director->GetPieza();
    /*FVector Location(0.0, 5, 185);
    FRotator Rotation(0.0, 0.0, 0.0);*/
    /*CurrentPiece = GetWorld()->SpawnActor<APiece>(Location, Rotation);*/
    //CurrentPiece = PiezaGenerada;
    bGameOver = CheckGameOver();
    if (bGameOver)
    {
        UE_LOG(LogTemp, Warning, TEXT("Game Over!!!!!!!!"));
        /*if (GameOverSoundCue)
        {
            UGameplayStatics::PlaySoundAtLocation(GetWorld(), GameOverSoundCue, GetActorLocation(), GetActorRotation());
        }*/
    }
}

void ABoard::CheckLine()
{
    auto MoveDownFromLine = [this](int z) {
        FVector Location(0.0f, 0.0f, 5.0 * z + 100.0);
        FRotator Rotation(0.0f, 0.0f, 0.0f);
        TArray<struct FOverlapResult> OutOverlaps;
        FCollisionShape CollisionShape;
        FVector Extent(4.5f, 49.5f, 95.0 + 4.5 - 5.0 * z);
        CollisionShape.SetBox(Extent);
        DrawDebugBox(GetWorld(), Location, Extent, FColor::Purple, false, 1, 0, 1);
        FCollisionQueryParams Params;
        FCollisionResponseParams ResponseParam;
        if (GetWorld()->OverlapMultiByChannel(OutOverlaps,
            Location, Rotation.Quaternion(), ECollisionChannel::ECC_WorldDynamic,
            CollisionShape, Params, ResponseParam))
        {
            for (auto&& Result : OutOverlaps)
            {
                FVector NewLocation = Result.GetActor()->GetActorLocation();
                NewLocation.Z -= 10.0f;
                Result.GetActor()->SetActorLocation(NewLocation);
            }
        }
    };

    int z = 0;
    while (z < 20)
    {
        FVector Location(0.0f, 0.0f, 10.0f * z + 5.0f);
        FRotator Rotation(0.0f, 0.0f, 0.0f);
        TArray<struct FOverlapResult> OutOverlaps;
        FCollisionShape CollisionShape;
        CollisionShape.SetBox(FVector(4.5f, 49.0f, 4.5f));
        //DrawDebugBox(GetWorld(), Location, FVector(4.5f, 10.0f, 4.5f), FColor::Purple, false, 1, 0, 1);
        FCollisionQueryParams Params;
        FCollisionResponseParams ResponseParam;
        bool b = GetWorld()->OverlapMultiByChannel(OutOverlaps,Location, Rotation.Quaternion(), ECollisionChannel::ECC_WorldDynamic, CollisionShape, Params, ResponseParam);
        if (!b || OutOverlaps.Num() < 10)
        {
            ++z;
            continue;
        }
        else // this line is full, remove the line
        {
            UE_LOG(LogTemp, Warning, TEXT("Find FULL LINE at z=%d"), z);
            for (auto&& Result : OutOverlaps)
            {
                /*Result.GetActor()->Destroy();*/
                AActor* actorPrueba=nullptr;
                actorPrueba = Result.GetActor();
                
                ((ABlock*)actorPrueba)->reducirVida();
                //actorPrueba->Destroy();  //OJO esto tenemos que eliminarlo una vez corregido linea completa
            }
            MoveDownFromLine(z);

            /*if (LineRemoveSoundCue)
            {
                UGameplayStatics::PlaySoundAtLocation(GetWorld(), LineRemoveSoundCue, GetActorLocation(), GetActorRotation());
            }*/
        }
    }
}

void ABoard::MoveDownToEnd()
{
    if (!CurrentPiece)
    {
        return;
    }

    while (CurrentPiece->MoveDown())
    {
    }

    /*if (MoveToEndSoundCue)
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), MoveToEndSoundCue, GetActorLocation(), GetActorRotation());
    }*/

    switch (Status)
    {
    case PS_MOVING:
        Status = PS_GOT_BOTTOM;
        CoolLeft = CoolDown;
        break;
    case PS_GOT_BOTTOM:
        break;
    default:
        UE_LOG(LogTemp, Warning, TEXT("Wrong status for MoveDownToEnd"));
        break;
    }
}

bool ABoard::CheckGameOver()
{
    if (!CurrentPiece)
    {
        UE_LOG(LogTemp, Warning, TEXT("NoPieces"));
        return true;
    }

    return CurrentPiece->CheckWillCollision([](FVector OldVector) { return OldVector; });
}
