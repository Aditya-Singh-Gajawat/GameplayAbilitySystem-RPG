// Aditya Singh Gajawat All Rights Reserved


#include "CharacterTypes/CharacterStructTypes.h"
#include "Abilities/MyWarriorGameplayAbility.h"

bool FWarriorHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
