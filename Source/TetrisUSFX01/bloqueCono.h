// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Block.h"
#include "bloqueCono.generated.h"

/**
 * 
 */
UCLASS()
class TETRISUSFX01_API AbloqueCono : public ABlock
{
	GENERATED_BODY()

public:
	AbloqueCono();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void reducirVida() override;
	void DestroyActor();
	UStaticMeshComponent* BlockMesh;
};
