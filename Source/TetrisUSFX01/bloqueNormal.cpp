// Fill out your copyright notice in the Description page of Project Settings.


#include "bloqueNormal.h"

AbloqueNormal::AbloqueNormal() {
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
		/*ConstructorHelpers::FObjectFinderOptional<UMaterial> Color_0;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> Color_1;*/
		/*ConstructorHelpers::FObjectFinderOptional<UMaterial> Color_0(TEXT("Material'/Game/Mesh/M_CobbleStone_Pebble.M_CobbleStone_Pebble'"));*/

		UMaterialInterface* MyMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/Mesh/M_Ground_Grass.M_Ground_Grass'"));
		UMaterialInterface* MyMaterial1 = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/Mesh/M_Metal_Rust.M_Metal_Rust'"));
		BlockMesh->SetMaterial(1, MyMaterial1);
		BlockMesh->SetMaterial(0, MyMaterial); 
		//BlockMesh->SetWorldScale3D(NuevaEscala);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No existe la malla para Block"));
	}
}
void AbloqueNormal::reducirVida() {
	/*UE_LOG(LogTemp, Log, TEXT("Bloque Normal, Vidas: %d"), vida);*/
	UE_LOG(LogTemp, Log, TEXT("Bloque Normal, Vidas: %d"), vida);
	--vida;
	if (vida <= 0) {
		DestroyActor();
	}
}

void AbloqueNormal::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(DestroyHandle, this, &AbloqueNormal::DestroyActor, 10.f, false);
}

// Called every frame
void AbloqueNormal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AbloqueNormal::DestroyActor() {
	Destroy();
}