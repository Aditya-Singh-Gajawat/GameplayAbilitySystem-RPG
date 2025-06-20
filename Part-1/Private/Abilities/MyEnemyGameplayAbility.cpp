// Aditya Singh Gajawat All Rights Reserved


#include "Abilities/MyEnemyGameplayAbility.h"
#include "Characters/MyEnemyCharacter.h"

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
