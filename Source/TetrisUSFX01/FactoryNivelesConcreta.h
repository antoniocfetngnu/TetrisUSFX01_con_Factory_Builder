// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NivelesFactoryInterfaz.h"
#include "FactoryNivelesConcreta.generated.h"


UCLASS()
class TETRISUSFX01_API AFactoryNivelesConcreta : public AActor, public INivelesFactoryInterfaz
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFactoryNivelesConcreta();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void cargarNivel(FString nombreNivel) override;

};
