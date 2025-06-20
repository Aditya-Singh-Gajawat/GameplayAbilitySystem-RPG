// Aditya Singh Gajawat All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/MyWarriorGameplayAbility.h"
#include "MyWarriorHeroGameplayAbility.generated.h"

class AMyWarriorHeroCharacter;
class AWarriorHeroController;
class UHeroCombatComponent;

UCLASS()
class GAS_RPG_API UMyWarriorHeroGameplayAbility : public UMyWarriorGameplayAbility
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	AMyWarriorHeroCharacter* GetMyWarriorHeroCharacterFromActorInfo();
	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	AWarriorHeroController* GetWarriorHeroControllerFromActorInfo();
	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();
private:
	TWeakObjectPtr<AMyWarriorHeroCharacter> CachedWarriorHeroCharacter;
	TWeakObjectPtr<AWarriorHeroController> CachedWarriorHeroController;
};
