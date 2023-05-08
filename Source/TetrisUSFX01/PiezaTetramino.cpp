// Fill out your copyright notice in the Description page of Project Settings.

#include "Pieza.h"
#include <vector>
#include "PiezaTetramino.h"

// Sets default values
APiezaTetramino::APiezaTetramino()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
void APiezaTetramino::spawnPieza() {

	if (Pieza == nullptr) {
		UE_LOG(LogTemp, Log, TEXT("NULLPTR DE PIEZA CRUZ!"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("SI HAY PIEZA! en PIEZA CRUZ"));
	}
	FVector Location(0.0, 5, 175);
	FRotator Rotation(0.0, 0.0, 0.0);
	Pieza = GetWorld()->SpawnActor<APieza>(APieza::StaticClass(), Location, Rotation);
	Pieza->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
}
void APiezaTetramino::buildBloques() {
	if (!Pieza) {
		UE_LOG(LogTemp, Error, TEXT("No hay pieza, es NULL, inicializala"));
		return;
	}
	else {
	std::vector<std::vector<std::pair<float, float>>> Shapes =
    {
        {{-20.0, 0.0}, {-10.0, 0.0}, {0.0, 0.0}, {10.0, 0.0}},
        {{0.0, 10.0}, {0.0, 0.0}, {10.0, 0.0}, {20.0, 0.0}},
        {{-20.0, 0.0}, {-10.0, 0.0}, {0.0, 0.0}, {0.0, 10.0}},
        {{0.0, 0.0}, {10.0, 0.0}, {0.0, -10.0}, {10.0, -10.0}},
        {{-10.0, -10.0}, {0.0, -10.0}, {0.0, 0.0}, {10.0, 0.0}},
        {{-10.0, 0.0}, {0.0, 0.0}, {0.0, 10.0}, {10.0, 0.0}},
        {{-10.0, 0.0}, {0.0, 0.0}, {0.0, -10.0}, {10.0, -10.0}},
    };
    const int Index = FMath::RandRange(0, Shapes.size() - 1);
    UE_LOG(LogTemp, Warning, TEXT("index=%d"), Index);

    const std::vector<std::pair<float, float>>& YZs = Shapes[Index];
	TMultiMap<FString, std::pair<float, float>> bloquesTmap;
	UE_LOG(LogTemp, Log, TEXT("LLENANDO TMAP!"));
	
	UE_LOG(LogTemp, Log, TEXT("Mandando A PIEZA!"));
	
    for (auto&& YZ : YZs)
    {
		bloquesTmap.Add(TEXT("color"), { YZ.first, YZ.second });
    }
	Pieza->setBloques(bloquesTmap);
	return;
	}
}
// Called when the game starts or when spawned
void APiezaTetramino::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APiezaTetramino::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
APieza* APiezaTetramino::GetPieza() {
	return Pieza;
}

