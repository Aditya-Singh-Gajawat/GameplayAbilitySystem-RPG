// Aditya Singh Gajawat All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MyWarriorGameplayAbility.generated.h"

class UPawnCombatComponent;
class UWarriorAbilitySystemComponent;

/*For activation policy*/
UENUM(BlueprintType)
enum class EAbilityActivationPolicy : uint8 
{
	OnTriggered,
	OnGiven
};

UENUM()
enum class EBaseCharactersSuccess:uint8
{
	Successed,
	Failed
};

UCLASS()
class GAS_RPG_API UMyWarriorGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
protected:
	//~ Begin UGameplayAbility Interface

	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	EAbilityActivationPolicy AbilityActivationPolicy = EAbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintPure, Category = "Base|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "Base|Ability")
	UWarriorAbilitySystemComponent* GetWarriorAbilitySystemComponentFromActorInfo() const;
	
	FActiveGameplayEffectHandle NativeGiveEffectSpecHandleToTarget(AActor* Target, const FGameplayEffectSpecHandle& InSpecHandle);
	
	UFUNCTION(BlueprintCallable, Category = "Base|Ability", meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Target Character", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_GiveEffectSpecHandleToTarget(AActor* Target, const FGameplayEffectSpecHandle& InSpecHandle, EBaseCharactersSuccess& OutSuccessType);
};
