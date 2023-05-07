// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BloquesFactory.h"
#include "FactoryNivel1.generated.h"

/**
 * 
 */
UCLASS()
class TETRISUSFX01_API AFactoryNivel1 : public ABloquesFactory
{
	GENERATED_BODY()
public:
	virtual ABlock* CrearBloque(FString nombreBloque) override;
	
};
