// Aditya Singh Gajawat All Rights Reserved


#include "Components/Combat/HeroCombatComponent.h"
#include "Items/Weapons/MyHeroWeapon.h"

AMyHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag)
{
    return Cast<AMyHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}
