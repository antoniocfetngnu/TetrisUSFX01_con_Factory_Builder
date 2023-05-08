// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BuilderPiezas.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pieza3Bloques.generated.h"

UCLASS()
class TETRISUSFX01_API APieza3Bloques : public AActor, public IBuilderPiezas
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APieza3Bloques();
	class APieza* Pieza;
	virtual void spawnPieza() override;
	virtual void buildBloques() override;
	virtual class APieza* GetPieza() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
