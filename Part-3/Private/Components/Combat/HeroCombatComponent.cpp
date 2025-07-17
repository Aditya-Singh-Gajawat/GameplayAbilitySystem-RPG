// Aditya Singh Gajawat All Rights Reserved


#include "Components/Combat/HeroCombatComponent.h"
#include "Characters/MyWarriorHeroCharacter.h"
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

int UHeroCombatComponent::LightAttackComboCounter()
{
    AMyWarriorHeroCharacter* Character =  Cast<AMyWarriorHeroCharacter>(GetOwningPawn());
    checkf(Character, TEXT("Failed to cast to MyHeroWarriorCharacter in the function LightAttackComboCounter"));
    return Character->ReturnMyHeroLightAttackComboCounter();
}

int UHeroCombatComponent::HeavyAttackComboCounter()
{
    AMyWarriorHeroCharacter* Character = Cast<AMyWarriorHeroCharacter>(GetOwningPawn());
    checkf(Character, TEXT("Failed to cast to MyHeroWarriorCharacter in the function LightAttackComboCounter"));
    return Character->ReturnMyHeroHeavyAttackComboCounter();
}


float UHeroCombatComponent::ReturnHeroCurrentEquippedWeaponDamageAsPerLevel(float InLevel) const
{
    return GetHeroCurrentEquippedWeapon()->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UHeroCombatComponent::OnHitTarget(AActor* HitActor)
{
    //Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT("OnHitTarget"));
    if (OverlappedActors.Contains(HitActor)) return;
    OverlappedActors.AddUnique(HitActor);

    FGameplayEventData Data;
    Data.Instigator = GetOwningPawn();
    Data.Target = HitActor;

    //SendGameplayEventToActor & listen for relevant to activate hit effects!

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor
    (
        GetOwningPawn(),
        WarriorGameplayTags::Shared_Event_RegisterHit,
        Data
    );
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor
    (
        GetOwningPawn(),
        WarriorGameplayTags::Player_Event_StickyAttackEffect,
        FGameplayEventData()
    );
}

void UHeroCombatComponent::OnAfterHitPulled(AActor* ActorHit)
{
    //On sending Player_Event_StickyAttackEffect to GetOwningPawn() which is our own player character. We execute HitPause Gameplay Ability, god I love GAS!
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor
    (
        GetOwningPawn(),
        WarriorGameplayTags::Player_Event_StickyAttackEffect,
        FGameplayEventData()
    );
}
