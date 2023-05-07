// BUILDER CONCRETO DE PIEZA CRUZ

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuilderPiezas.h"
#include "bloqueNormal.h"
#include "PiezaCruz.generated.h"

UCLASS()
class TETRISUSFX01_API APiezaCruz : public AActor, public IBuilderPiezas
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APiezaCruz();
	AbloqueNormal* Actor;
	class APieza* Pieza;
	virtual void buildBloques() override;
	virtual class APieza* GetPieza() override;
	virtual void spawnPieza() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
