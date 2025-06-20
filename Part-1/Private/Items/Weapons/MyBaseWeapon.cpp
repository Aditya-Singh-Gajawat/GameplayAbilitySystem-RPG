// Aditya Singh Gajawat All Rights Reserved


#include "Items/Weapons/MyBaseWeapon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AMyBaseWeapon::AMyBaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WeaponStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponStaticMesh"));
	WeaponStaticMesh->SetupAttachment(GetRootComponent());
	WeaponStaticMesh->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Ignore);
	WeaponStaticMesh->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Ignore);

	WeaponBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponBoxCollisionComponent"));
	WeaponBoxComp->SetupAttachment(GetRootComponent());
	WeaponBoxComp->SetBoxExtent(FVector(20.f));
	WeaponBoxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision); //Enable collision during damage detection
}

// Called when the game starts or when spawned
void AMyBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyBaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

