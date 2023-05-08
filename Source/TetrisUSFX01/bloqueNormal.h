// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Block.h"
#include "bloqueNormal.generated.h"

/**
 * 
 */
UCLASS()
class TETRISUSFX01_API AbloqueNormal : public ABlock
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AbloqueNormal();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void reducirVida() override;

	UPROPERTY()
	UStaticMeshComponent* BlockMesh;
private:
	FTimerHandle DestroyHandle;
	void DestroyActor();
};
