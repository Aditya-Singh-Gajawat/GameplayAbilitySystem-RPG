// Aditya Singh Gajawat All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBaseWeapon.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class GAS_RPG_API AMyBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyBaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleDefaultsOnly, Category = "Basic Components")
	UStaticMeshComponent* WeaponStaticMesh;
	UPROPERTY(VisibleDefaultsOnly, Category = "Basic Components")
	UBoxComponent* WeaponBoxComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
