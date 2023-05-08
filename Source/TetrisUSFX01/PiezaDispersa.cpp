// Fill out your copyright notice in the Description page of Project Settings.

#include "Pieza.h"
#include "PiezaDispersa.h"

// Sets default values
APiezaDispersa::APiezaDispersa()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
void APiezaDispersa::spawnPieza() {

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
// Called when the game starts or when spawned
void APiezaDispersa::BeginPlay()
{
	Super::BeginPlay();
	//FVector Location(0.0, 5, 175);
	//FRotator Rotation(0.0, 0.0, 0.0);
	//Pieza = GetWorld()->SpawnActor<APieza>(APieza::StaticClass(),Location,Rotation);
	////Attach it to the Builder (this)
	//Pieza->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called every frame
void APiezaDispersa::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void APiezaDispersa::buildBloques() {
	if (!Pieza) {
		UE_LOG(LogTemp, Error, TEXT("No hay pieza, es NULL, inicializala"));
		return;
	}
	else {
		TMultiMap<FString, std::pair<float, float>> bloquesTmap;
		UE_LOG(LogTemp, Log, TEXT("LLENANDO TMAP!"));

		bloquesTmap.Add(TEXT("color"), { -10,0 });
		bloquesTmap.Add(TEXT("color"), { 10,0 });
		bloquesTmap.Add(TEXT("color"), { -10,-20 });

		UE_LOG(LogTemp, Log, TEXT("Mandando A PIEZA!"));
		Pieza->setBloques(bloquesTmap);

		return;
	}

}

APieza* APiezaDispersa::GetPieza() {
	return Pieza;
}


