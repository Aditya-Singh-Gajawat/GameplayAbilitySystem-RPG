// Aditya Singh Gajawat All Rights Reserved


#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "Ability System/WarriorAbilitySystemComponent.h"
#include "Abilities/MyWarriorGameplayAbility.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	checkf(InASCToGive, TEXT("Can't give ability to Ability System Component"));
	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);
	if (!StartUpGameplayEffects.IsEmpty())
	{
		for(const TSubclassOf <UGameplayEffect>& GE_Class : StartUpGameplayEffects)
		{
			if (!GE_Class) continue;
			UGameplayEffect* EffectDefaultObject = GE_Class->GetDefaultObject<UGameplayEffect>();
			InASCToGive->ApplyGameplayEffectToSelf
			(
				EffectDefaultObject,
				ApplyLevel,
				InASCToGive->MakeEffectContext()
			);
		}
	}
}

void UDataAsset_StartUpDataBase::GrantAbilities(TArray<TSubclassOf<UMyWarriorGameplayAbility>>& InAbilitiesToGive, UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty()) return;
	for(const TSubclassOf<UMyWarriorGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;
		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
