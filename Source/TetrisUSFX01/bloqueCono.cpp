// Fill out your copyright notice in the Description page of Project Settings.


#include "bloqueCono.h"


AbloqueCono::AbloqueCono() {
	PrimaryActorTick.bCanEverTick = true;
	vida = 3;
	//imprimirNombre();
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));
	RootComponent = BlockMesh;
	
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> BlockMeshAsset(TEXT("StaticMesh'/Game/Mesh/block.block'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BlockMeshAsset(TEXT("StaticMesh'/Game/Mesh/block.block'"));

	if (BlockMeshAsset.Succeeded())
	{
		BlockMesh->SetStaticMesh(BlockMeshAsset.Object);
		/*FVector NuevaEscala = FVector(0.03f, 0.03f, 0.03f);*/
		BlockMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		//BlockMesh->SetWorldScale3D(NuevaEscala);
		UMaterialInterface* MyMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/Mesh/M_CobbleStone_Pebble.M_CobbleStone_Pebble'"));
		UMaterialInterface* MyMaterial1 = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/Mesh/M_CobbleStone_Rough.M_CobbleStone_Rough'"));
		BlockMesh->SetMaterial(1, MyMaterial1);
		BlockMesh->SetMaterial(0, MyMaterial);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No existe la malla para Block"));
	}
}
void AbloqueCono::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AbloqueCono::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AbloqueCono::reducirVida() {
	UE_LOG(LogTemp, Log, TEXT("Bloque Cono, Vidas: %d"),vida);
	--vida;
	if (vida <= 0) {
		DestroyActor();
	}
}
void AbloqueCono::DestroyActor() {
	Destroy();
}