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
	UFUNCTION(BlueprintPure, Category = "Hero|Ability")
	AMyWarriorHeroCharacter* GetMyWarriorHeroCharacterFromActorInfo();
	UFUNCTION(BlueprintPure, Category = "Hero|Ability")
	AWarriorHeroController* GetWarriorHeroControllerFromActorInfo();
	UFUNCTION(BlueprintPure, Category = "Hero|Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "Hero|Ability")
	FGameplayEffectSpecHandle InitializeHeroGameplayEffectSpecHandle(TSubclassOf<UGameplayEffect> GameplayEffectClass, float InWeaponBaseDamage,
		FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount);
private:
	TWeakObjectPtr<AMyWarriorHeroCharacter> CachedWarriorHeroCharacter;
	TWeakObjectPtr<AWarriorHeroController> CachedWarriorHeroController;
};
