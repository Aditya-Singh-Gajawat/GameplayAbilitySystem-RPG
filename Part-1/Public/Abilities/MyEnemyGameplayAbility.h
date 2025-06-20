// Aditya Singh Gajawat All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/MyWarriorGameplayAbility.h"
#include "MyEnemyGameplayAbility.generated.h"

class AMyEnemyCharacter;
class UEnemyCombatComponent;

UCLASS()
class GAS_RPG_API UMyEnemyGameplayAbility : public UMyWarriorGameplayAbility
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	AMyEnemyCharacter* GetMyEnemyCharacterFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();
private:
	TWeakObjectPtr<AMyEnemyCharacter> CachedEnemyCharacter;
};
