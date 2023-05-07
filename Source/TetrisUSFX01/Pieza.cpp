// Fill out your copyright notice in the Description page of Project Settings.

#include "FactoryNivel1.h"
#include "Pieza.h"

#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include <vector>
// Sets default values
APieza::APieza()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SceneComponent = CreateDefaultSubobject<USceneComponent>("Pieces Scene");
    RootComponent = SceneComponent;
}

// Called when the game starts or when spawned
void APieza::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APieza::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APieza::setBloques(TMultiMap<FString, std::pair<float, float>>& TipoBloqueYposicion) {
    AFactoryNivel1* FabricaNivel1a = GetWorld()->SpawnActor<AFactoryNivel1>(AFactoryNivel1::StaticClass());
    ABlock* BloqueX;
    for (auto& Elem : TipoBloqueYposicion)
    {
        FString tipoBloque = Elem.Key;
        std::pair<float, float> posicion = Elem.Value;
        UE_LOG(LogTemp, Log, TEXT("ITERANDO TMULTIMAP; DEBERIA APARECER 5 VECES (5 bloques)!!"));
       /* UE_LOG(LogTemp, Log, TEXT("Posicion: %d, Tipo de Pieza: %s"), pos, *data[0]);
        UE_LOG(LogTemp, Log, TEXT("Coordenadas: %s, Fecha Creacion: %s"), *data[2], *data[1]);*/
        BloqueX = FabricaNivel1a->CrearBloque(tipoBloque);
        BloqueX->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
        BloqueX->SetActorRelativeLocation(FVector(0.0, posicion.first, posicion.second));
        Blocks.Add(BloqueX);
    }
}

void APieza::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    UE_LOG(LogTemp, Warning, TEXT("Piezas eliminadas"));
}
void APieza::DrawDebugLines()
{
    for (ABlock* B : Blocks)
    {
        FVector V1 = B->GetActorLocation();
        FVector V2(V1.X, V1.Y, 5.0f);
        DrawDebugLine(GetWorld(), V1, V2, FColor::Green, false, 1, 0, 1);
    }
}

void APieza::TestRotate()
{
    auto RotateVector = [this](FVector OldVector) {
        FVector ActorVector = this->GetActorLocation();
        FVector BlockVector = OldVector;
        FVector TempVector = BlockVector - ActorVector;
        TempVector = ActorVector + TempVector.RotateAngleAxis(90.0, FVector(1.0, 0.0, 0.0));
        return TempVector;
    };

    if (!CheckWillCollision(RotateVector))
    {
        UE_LOG(LogTemp, Warning, TEXT("now can rotate"));
        FRotator NewRotation = this->GetActorRotation() + FRotator(0.0, 0.0, -90.0);
        //FRotator NewRotation = this->GetActorRotation() + FRotator(90.0, 0.0, 0.0);
        this->SetActorRelativeRotation(NewRotation);
        /*if (RotateSoundCue)
        {
            UGameplayStatics::PlaySoundAtLocation(GetWorld(), RotateSoundCue, GetActorLocation(), GetActorRotation());
        }*/
    }
}



//void APiece::EndPlay(const EEndPlayReason::Type EndPlayReason)
//{
//    UE_LOG(LogTemp, Warning, TEXT("Pieces Deleted"));
//}

void APieza::Dismiss()
{
    Blocks.Empty();
}

void APieza::MoveLeft()
{
    auto MoveVectorLeft = [](FVector OldVector) {
        OldVector.Y -= 10.0f;
        return OldVector;
    };

    if (!CheckWillCollision(MoveVectorLeft))
    {
        FVector NewLocation = GetActorLocation();
        NewLocation.Y -= 10;
        SetActorLocation(NewLocation);

        /* if (MoveLeftRightSoundCue)
         {
             UGameplayStatics::PlaySoundAtLocation(GetWorld(), MoveLeftRightSoundCue, GetActorLocation(), GetActorRotation());
         }*/
    }
}

void APieza::MoveRight()
{
    auto MoveVectorRight = [](FVector OldVector) {
        OldVector.Y += 10.0f;
        return OldVector;
    };

    if (!CheckWillCollision(MoveVectorRight))
    {
        FVector NewLocation = GetActorLocation();
        NewLocation.Y += 10;
        SetActorLocation(NewLocation);

        /*if (MoveLeftRightSoundCue)
        {
            UGameplayStatics::PlaySoundAtLocation(GetWorld(), MoveLeftRightSoundCue, GetActorLocation(), GetActorRotation());
        }*/
    }
}

bool APieza::MoveDown(bool PlaySound)
{
    auto MoveVectorDown = [](FVector OldVector) {
        OldVector.Z -= 10.0f;
        return OldVector;
    };

    if (!CheckWillCollision(MoveVectorDown))
    {
        FVector NewLocation = GetActorLocation();
        NewLocation.Z -= 10;
        SetActorLocation(NewLocation);

        return true;
    }
    else
    {
        return false;
    }
}

bool APieza::CheckWillCollision(std::function<FVector(FVector OldLocation)> ChangeBeforeCheck)
{
    FCollisionQueryParams Params;
    for (ABlock* B : Blocks)
    {
        Params.AddIgnoredActor(B);
    }

    for (ABlock* B : Blocks)
    {
        FVector TempVector = B->GetActorLocation();
        TempVector = ChangeBeforeCheck(TempVector);

        TArray<struct FOverlapResult> OutOverlaps;
        FCollisionShape CollisionShape;
        CollisionShape.SetBox(FVector(4.0f, 4.0f, 4.0f));
        FCollisionResponseParams ResponseParam;
        bool b = GetWorld()->OverlapMultiByChannel(OutOverlaps,
            TempVector, B->GetActorQuat(), ECollisionChannel::ECC_WorldDynamic,
            CollisionShape, Params, ResponseParam);

        if (b)
        {
            for (auto&& Result : OutOverlaps)
            {
                UE_LOG(LogTemp, Warning, TEXT("OverLapped with actor %s, component=%s"), *Result.GetActor()->GetName(),
                    *Result.GetComponent()->GetName());
                /*if (Result.GetActor()->GetName() == "Cube_6") {
                    UE_LOG(LogTemp, Warning, TEXT("Puntuacion aumentada"));
                    puntuacion = puntuacion+10;
                    UE_LOG(LogTemp, Warning, TEXT("Puntuacion Actual: %d"),puntuacion);
                }*/

            }
            return true;
        }
    }

    return false;
}

