// Aditya Singh Gajawat All Rights Reserved


#include "Abilities/MyEnemyGameplayAbility.h"
#include "Characters/MyEnemyCharacter.h"
#include "Ability System/WarriorAbilitySystemComponent.h"
#include "GameplayTag/MyGameplayTags.h"

AMyEnemyCharacter* UMyEnemyGameplayAbility::GetMyEnemyCharacterFromActorInfo()
{
	if(!CachedEnemyCharacter.IsValid())
	{
		CachedEnemyCharacter = Cast<AMyEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedEnemyCharacter.IsValid() ? CachedEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UMyEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetMyEnemyCharacterFromActorInfo()->ReturnEnemyCombatComponent();
}

FGameplayEffectSpecHandle UMyEnemyGameplayAbility::InitializeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> GameplayEffectClass, const FScalableFloat InScalableFloatDamage)
{
	check(GameplayEffectClass);
	//Defining Context Handle
	FGameplayEffectContextHandle ContextHandle = GetWarriorAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
	//Defining EffectSpecHandle
	FGameplayEffectSpecHandle EffectSpecHandle = GetWarriorAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec
	(
		GameplayEffectClass,
		GetAbilityLevel(),
		ContextHandle
	);
	//Set up variables 
	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		WarriorGameplayTags::Shared_EffectSpec_BaseDamage,
		InScalableFloatDamage.GetValueAtLevel(GetAbilityLevel())
		);

	return EffectSpecHandle;
}
