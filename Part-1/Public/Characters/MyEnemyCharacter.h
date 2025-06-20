// Aditya Singh Gajawat All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/WarriorBaseCharacter.h"
#include "MyEnemyCharacter.generated.h"

class UEnemyCombatComponent;

UCLASS()
class GAS_RPG_API AMyEnemyCharacter : public AWarriorBaseCharacter
{
	GENERATED_BODY()
private:
	void InitializeEnemyStartUpDataAsset();
public:
	AMyEnemyCharacter();
	FORCEINLINE UEnemyCombatComponent* ReturnEnemyCombatComponent() const { return EnemyCombatComponent; }
protected:
	//~ Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UEnemyCombatComponent* EnemyCombatComponent;
};
