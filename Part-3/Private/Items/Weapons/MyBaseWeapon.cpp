// Aditya Singh Gajawat All Rights Reserved


#include "Items/Weapons/MyBaseWeapon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Blueprint Function Library/CharacterBluprintFunctionLibrary.h"

#include "WarriorDebugHelper.h"
// Sets default values
AMyBaseWeapon::AMyBaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponStaticMesh"));
	SetRootComponent(WeaponStaticMesh);

	WeaponBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponBoxCollisionComponent"));
	WeaponBoxComp->SetupAttachment(GetRootComponent());
	WeaponBoxComp->SetBoxExtent(FVector(20.f));
	WeaponBoxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision); //Enable collision during damage detection
	WeaponBoxComp->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
	WeaponBoxComp->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxEndOverlap);
}

// Called when the game starts or when spawned
void AMyBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AMyBaseWeapon::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();
	checkf(WeaponOwningPawn, TEXT("Forgot to assign instigator for owning pawn for weapon: %s"), *GetName());

	if(APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if(UCharacterBluprintFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn, HitPawn))
		{
			OnWeaponHit.ExecuteIfBound(OtherActor);
		}
	}
}

void AMyBaseWeapon::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();
	checkf(WeaponOwningPawn, TEXT("Forgot to assign instigator for owning pawn for weapon: %s"), *GetName());
	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UCharacterBluprintFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn, HitPawn))
		{
			OnWeaponPulled.ExecuteIfBound(OtherActor);
		}
	}
}

// Called every frame
void AMyBaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

