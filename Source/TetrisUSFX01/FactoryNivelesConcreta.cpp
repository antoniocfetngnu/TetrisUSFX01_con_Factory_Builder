// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "FactoryNivelesConcreta.h"

// Sets default values
AFactoryNivelesConcreta::AFactoryNivelesConcreta()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFactoryNivelesConcreta::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFactoryNivelesConcreta::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void  AFactoryNivelesConcreta::cargarNivel(FString nombreNivel) {
	if (nombreNivel == "MapaTetris") {
		UE_LOG(LogTemp, Warning, TEXT("CARGANDO NIVEL 1!!!!!!"));
		UGameplayStatics::OpenLevel(GetWorld(), FName("MapaTetris"));

	}
	else if (nombreNivel == "MapaTetris2") {
		UE_LOG(LogTemp, Warning, TEXT("CARGANDO NIVEL 2!!!!!!"));
		UGameplayStatics::OpenLevel(GetWorld(), FName("MapaTetris2"));
	}
	else if (nombreNivel == "MapaTetris3") {
		UE_LOG(LogTemp, Warning, TEXT("CARGANDO NIVEL 3!!!!!!"));
		UGameplayStatics::OpenLevel(GetWorld(), FName("MapaTetris3"));
	}

}

