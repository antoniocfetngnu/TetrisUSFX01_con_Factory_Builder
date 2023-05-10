// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TetrisUSFX01GameModeBase.generated.h"

UCLASS()
class TETRISUSFX01_API ATetrisUSFX01GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
private:
	void crearNuevoBoard();
protected:
	virtual void BeginPlay() override;

public:
	ATetrisUSFX01GameModeBase();
	FTimerHandle crearBoard;
	//void GetLevelName();
};
