// Aditya Singh Gajawat All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBaseEquipment.generated.h"

UCLASS()
class GAS_RPG_API AMyBaseEquipment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyBaseEquipment();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleDefaultsOnly, Category = "Basic Components")
	UStaticMeshComponent* EquipmentStaticMesh;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
