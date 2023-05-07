// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Block.h"
#include "bloqueRedondo.generated.h"

/**
 * 
 */
UCLASS()
class TETRISUSFX01_API AbloqueRedondo : public ABlock
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AbloqueRedondo();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void reducirVida() override;
	void DestroyActor();
	UPROPERTY()
	UStaticMeshComponent* BlockMesh;
	
};
