// Fill out your copyright notice in the Description page of Project Settings.


#include "bloqueRedondo.h"
AbloqueRedondo::AbloqueRedondo() {
	PrimaryActorTick.bCanEverTick = true;
	vida = 1;
	//imprimirNombre();
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));
	RootComponent = BlockMesh;

	//static ConstructorHelpers::FObjectFinder<UStaticMesh> BlockMeshAsset(TEXT("StaticMesh'/Game/Mesh/block.block'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BlockMeshAsset(TEXT("StaticMesh'/Game/Mesh/block.block'"));

	if (BlockMeshAsset.Succeeded())
	{
		BlockMesh->SetStaticMesh(BlockMeshAsset.Object);
		//FVector NuevaEscala = FVector(0.08f, 0.08f, 0.08f);
		BlockMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		UMaterialInterface* MyMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/Mesh/Material_004_002.Material_004_002'"));
		UMaterialInterface* MyMaterial1 = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/Mesh/Material_0.Material_0'"));
		BlockMesh->SetMaterial(1, MyMaterial1);
		BlockMesh->SetMaterial(0, MyMaterial);
		//BlockMesh->SetWorldScale3D(NuevaEscala);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No existe la malla para Block"));
	}
}
void AbloqueRedondo::reducirVida() {
	UE_LOG(LogTemp, Log, TEXT("Bloque Esferico, Vidas: %d"), vida);
	--vida;
	if (vida <= 0) {
		DestroyActor();
	}
}

void AbloqueRedondo::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AbloqueRedondo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AbloqueRedondo::DestroyActor() {
	Destroy();
}