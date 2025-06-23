// Aditya Singh Gajawat All Rights Reserved


#include "Abilities/MyWarriorHeroGameplayAbility.h"
#include "Characters/MyWarriorHeroCharacter.h"
#include "Controllers/WarriorHeroController.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "Ability System/WarriorAbilitySystemComponent.h"
#include "GameplayTag/MyGameplayTags.h"

AMyWarriorHeroCharacter* UMyWarriorHeroGameplayAbility::GetMyWarriorHeroCharacterFromActorInfo()
{
	if(!CachedWarriorHeroCharacter.IsValid())
	{
		CachedWarriorHeroCharacter = Cast<AMyWarriorHeroCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedWarriorHeroCharacter.IsValid() ? CachedWarriorHeroCharacter.Get() : nullptr;
}

AWarriorHeroController* UMyWarriorHeroGameplayAbility::GetWarriorHeroControllerFromActorInfo()
{
	if(!CachedWarriorHeroController.IsValid())
	{
		CachedWarriorHeroController = Cast<AWarriorHeroController>(CurrentActorInfo->PlayerController);
	}
	return CachedWarriorHeroController.IsValid() ? CachedWarriorHeroController.Get() : nullptr;
}

UHeroCombatComponent* UMyWarriorHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	return GetMyWarriorHeroCharacterFromActorInfo()->ReturnMyHeroCombatComponent();
}

FGameplayEffectSpecHandle UMyWarriorHeroGameplayAbility::InitializeHeroGameplayEffectSpecHandle(TSubclassOf<UGameplayEffect> GameplayEffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount)
{
	//Assign correctly, else the editor crashes
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
	EffectSpecHandle.Data->SetSetByCallerMagnitude(WarriorGameplayTags::Shared_EffectSpec_BaseDamage, InWeaponBaseDamage);
	if (InCurrentAttackTypeTag.IsValid()) EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
	
	return EffectSpecHandle;
}
