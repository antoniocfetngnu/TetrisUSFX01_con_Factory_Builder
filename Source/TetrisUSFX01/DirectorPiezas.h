// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuilderPiezas.h"
#include "DirectorPiezas.generated.h"

UCLASS()
class TETRISUSFX01_API ADirectorPiezas : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADirectorPiezas();
	IBuilderPiezas* BuilderPiezas;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Crea las piezas			--constructPiece
	void ConstruirPieza();
	//Asignar el Actor Builder	--setPieceConstructor
	void AsignarConstructorDePieza(AActor* Builder);
	//Obtener la Pieza del Builder --getPieza
	class APieza* GetPieza();
};
