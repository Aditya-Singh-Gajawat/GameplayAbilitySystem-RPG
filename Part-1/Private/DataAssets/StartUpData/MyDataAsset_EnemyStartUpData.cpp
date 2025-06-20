// Aditya Singh Gajawat All Rights Reserved


#include "DataAssets/StartUpData/MyDataAsset_EnemyStartUpData.h"
#include "Abilities/MyEnemyGameplayAbility.h"
#include "Ability System/WarriorAbilitySystemComponent.h"

void UMyDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);
	if (!EnemyCombatAbilities.IsEmpty())
	{
		for (const TSubclassOf<UMyEnemyGameplayAbility> Ability : EnemyCombatAbilities)
		{
			if (!Ability) continue;
			FGameplayAbilitySpec AbilitySpec(Ability);
			AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;

			InASCToGive->GiveAbility(AbilitySpec);
		}

	}
}
