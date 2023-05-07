// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectorPiezas.h"


// Sets default values
ADirectorPiezas::ADirectorPiezas()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADirectorPiezas::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADirectorPiezas::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ADirectorPiezas::AsignarConstructorDePieza(AActor* Builder)
{
	//Cast the passed Actor and set the Builder
	BuilderPiezas = Cast<IBuilderPiezas>(Builder);
	if (!BuilderPiezas) //Log Error if cast fails
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("CAST Inválido!!!!!!!!!"));
	}
}

APieza* ADirectorPiezas::GetPieza()
{
	if (BuilderPiezas)
	{
		//Returns the Lodging of the Builder
		return BuilderPiezas->GetPieza();
	}
	//Log if the Builder is NULL
	UE_LOG(LogTemp, Error, TEXT("Erro en GetPieza, retornando nullptr!!!!!!!"));
	return nullptr;
}
void ADirectorPiezas::ConstruirPieza()
{
	/*UWorld* World = GetWorld();*/


	//Log if the Builder is NULL
	if (!BuilderPiezas) {
		UE_LOG(LogTemp, Error,TEXT("El builder es NULL, asegurate de inicializarlo!!!!!!!!!")); return; 
					}
		//Creates the buildings
		BuilderPiezas->spawnPieza();
		BuilderPiezas->buildBloques();
}
