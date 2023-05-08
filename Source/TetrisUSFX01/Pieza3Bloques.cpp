// Fill out your copyright notice in the Description page of Project Settings.

#include "Pieza.h"
#include <vector>
#include "Pieza3Bloques.h"

// Sets default values
APieza3Bloques::APieza3Bloques()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APieza3Bloques::BeginPlay()
{
	Super::BeginPlay();
	
}
void APieza3Bloques::spawnPieza() {

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
void APieza3Bloques::buildBloques() {
	if (!Pieza) {
		UE_LOG(LogTemp, Error, TEXT("No hay pieza, es NULL, inicializala"));
		return;
	}
	else {
		std::vector<std::vector<std::pair<float, float>>> Shapes =
		{
			{{-20.0, -20.0}, {-10.0, -10.0}, {0.0, 0.0}},
			{{-10.0, -10.0}, {0.0, -10.0}, {10.0, -10.0},},
			{{-0.0, -10.0}, {-10.0, -10.0}, {-10.0, -20.0}},
		};
		const int Index = FMath::RandRange(0, Shapes.size() - 1);
		UE_LOG(LogTemp, Warning, TEXT("index=%d"), Index);

		const std::vector<std::pair<float, float>>& YZs = Shapes[Index];
		TMultiMap<FString, std::pair<float, float>> bloquesTmap;
		UE_LOG(LogTemp, Log, TEXT("LLENANDO TMAP!"));

		UE_LOG(LogTemp, Log, TEXT("Mandando A PIEZA!"));
		int i = 0;
		for (auto&& YZ : YZs)
		{
			bloquesTmap.Add(TEXT("color"), { YZ.first, YZ.second });
				/*if(i=0){
				bloquesTmap.Add(TEXT("color"), { YZ.first, YZ.second });
				i++;
			}
			else if(i=1)
			{
				bloquesTmap.Add(TEXT("temporal"), { YZ.first, YZ.second });
				i++;
			}	
			else 
				bloquesTmap.Add(TEXT("temporal"), { YZ.first, YZ.second });*/
		}
		Pieza->setBloques(bloquesTmap);
		return;
	}
}
APieza* APieza3Bloques::GetPieza() {
	return Pieza;
}
// Called every frame
void APieza3Bloques::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

