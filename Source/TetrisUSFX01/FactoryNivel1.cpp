// Fill out your copyright notice in the Description page of Project Settings.


#include "FactoryNivel1.h"
#include "bloqueCono.h"
#include "bloqueRedondo.h"
#include "bloqueNormal.h"

ABlock* AFactoryNivel1::CrearBloque(FString nombreBloque)
{
	//Select which potion to spawn depending on the passed string
	if (nombreBloque.Equals("temporal")) {
		return GetWorld()->SpawnActor<AbloqueCono>
			(AbloqueCono::StaticClass());
	}
	else if (nombreBloque.Equals("normal")) {
		return GetWorld()->SpawnActor<AbloqueNormal>
			(AbloqueNormal::StaticClass());
	}
	else if (nombreBloque.Equals("postDest")) {
		return GetWorld()->SpawnActor<AbloqueRedondo>
			(AbloqueRedondo::StaticClass());
	}
	else return nullptr; //Return null if the string isn't valid
}

