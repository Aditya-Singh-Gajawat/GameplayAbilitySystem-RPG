// Aditya Singh Gajawat All Rights Reserved

#pragma once
 
#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CharacterTypes/CharacterStructTypes.h"
#include "WarriorAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API UWarriorAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:

#pragma region Trigger based Gameplay Abilities
	/*Functions below are for Trigger based Gameplay Abilities, like Equiping Weapon when key is pressed. Called in MyWarriorHeroCharacter*/
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);
#pragma endregion

#pragma region Functions to grant WEAPON abilities to ASC 
	UFUNCTION(BlueprintCallable, meta = (ApplyLevel = "1"))
	void GrantHeroWeaponAbilities(const TArray<FWarriorHeroAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);

	UFUNCTION(BlueprintCallable)
	void RemovedGrantedWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove);

	UFUNCTION(BlueprintCallable)
	bool TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate);
#pragma endregion
};
