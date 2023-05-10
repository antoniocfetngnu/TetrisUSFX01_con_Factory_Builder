// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pieza.h"
#include "FactoryNivelesConcreta.h"
#include "Board.generated.h"

UCLASS()
class TETRISUSFX01_API ABoard : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABoard();
	AFactoryNivelesConcreta* FabricaEscenas; //Fabrica de escenarios con FACTORY

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
		APieza* CurrentPiece;

	void Rotate();
	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void NewPiece();
	void CheckLine();
	void MoveDownToEnd();
	void CambiarNivel1();
	void CambiarNivel2();
	void CambiarNivel3();
	//The Builder Actor
	UPROPERTY(VisibleAnywhere, Category = "Principal")
		class APiezaCruz* PiezaCruzBuilder;
	UPROPERTY(VisibleAnywhere, Category = "Principal")
		class APiezaDispersa* PiezaDispersaBuilder;
	UPROPERTY(VisibleAnywhere, Category = "Principal")
		class APiezaTetramino* PiezaTetraminoBuilder;
	UPROPERTY(VisibleAnywhere, Category = "Principal")
		class APiezaLineaPunteada* PiezaLineaPunteadaBuilder;
	UPROPERTY(VisibleAnywhere, Category = "Principal")
		class APieza3Bloques* Pieza3BloquesBuilder;
	//The Engineer Actor
	UPROPERTY(VisibleAnywhere, Category = "Principal")
		class ADirectorPiezas* Director;

private:
	enum PieceStatus { PS_NOT_INITED, PS_MOVING, PS_GOT_BOTTOM };
	PieceStatus Status = PS_NOT_INITED;

	const float CoolDown = 0.3f;
	float CoolLeft = 0.3f;
	bool bGameOver = false;

	bool CheckGameOver();
	//-----------------------------------//

	
};
