// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Block.h"
#include "bloqueRedondo.h"
#include "bloqueNormal.h"
#include "bloqueCono.h"

#include <functional>
#include "Pieza.generated.h"

UCLASS()
class TETRISUSFX01_API APieza : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APieza();
	TArray<ABlock*> Blocks;
	void setBloques(TMultiMap<FString, std::pair<float, float>>& TipoBloqueYposicion);
	UPROPERTY()
		class USceneComponent* SceneComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DrawDebugLines();
	void TestRotate();
	void MoveLeft();
	void MoveRight();
	bool MoveDown(bool PlaySound = true);
	void Dismiss();
	bool CheckWillCollision(std::function<FVector(FVector OldLocation)> ChangeBeforeCheck);

};
