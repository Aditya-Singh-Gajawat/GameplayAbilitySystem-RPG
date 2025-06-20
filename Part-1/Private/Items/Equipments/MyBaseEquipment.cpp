// Aditya Singh Gajawat All Rights Reserved


#include "Items/Equipments/MyBaseEquipment.h"

// Sets default values
AMyBaseEquipment::AMyBaseEquipment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EquipmentStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Equipment Static Mesh"));
	EquipmentStaticMesh->SetupAttachment(GetRootComponent());
	EquipmentStaticMesh->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Ignore);
	EquipmentStaticMesh->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Ignore);
}

// Called when the game starts or when spawned
void AMyBaseEquipment::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyBaseEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

