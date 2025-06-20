// Aditya Singh Gajawat All Rights Reserved


#include "Abilities/MyWarriorHeroGameplayAbility.h"
#include "Characters/MyWarriorHeroCharacter.h"
#include "Controllers/WarriorHeroController.h"
#include "Components/Combat/HeroCombatComponent.h"

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