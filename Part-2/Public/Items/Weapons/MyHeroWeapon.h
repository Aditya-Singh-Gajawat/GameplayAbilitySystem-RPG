// Aditya Singh Gajawat All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/MyBaseWeapon.h"
#include "CharacterTypes/CharacterStructTypes.h"
#include "GameplayAbilitySpecHandle.h"
#include "MyHeroWeapon.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API AMyHeroWeapon : public AMyBaseWeapon
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FCharacterHeroWeaponData HeroWeaponData;
	
	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);
	
	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;

private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
