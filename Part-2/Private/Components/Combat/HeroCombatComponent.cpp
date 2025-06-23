// Aditya Singh Gajawat All Rights Reserved


#include "Components/Combat/HeroCombatComponent.h"
#include "Items/Weapons/MyHeroWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTag/MyGameplayTags.h"

#include "WarriorDebugHelper.h"

AMyHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag)
{
    return Cast<AMyHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

AMyHeroWeapon* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
    return Cast<AMyHeroWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UHeroCombatComponent::ReturnHeroCurrentEquippedWeaponDamageAsPerLevel(float InLevel) const
{
    return GetHeroCurrentEquippedWeapon()->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UHeroCombatComponent::OnHitTarget(AActor* HitActor)
{
    if (OverlappedActors.Contains(HitActor)) return;
    OverlappedActors.AddUnique(HitActor);

    FGameplayEventData Data;
    Data.Instigator = GetOwningPawn();
    Data.Target = HitActor;

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor
    (
        GetOwningPawn(),
        WarriorGameplayTags::Shared_Event_RegisterHit,
        Data
    );
}

void UHeroCombatComponent::OnAfterHitPulled(AActor* ActorHit)
{

}
