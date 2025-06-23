// Aditya Singh Gajawat All Rights Reserved
#include "Components/Combat/PawnCombatComponent.h"
#include "Items/Weapons/MyBaseWeapon.h"
#include "Components/BoxComponent.h"

#include "WarriorDebugHelper.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AMyBaseWeapon* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	//IF condition returns false then WeaponTag is already added to TMap before, don't want to add it again.
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("A %s has already been added as carried weapon"), *InWeaponTagToRegister.ToString());
	check(InWeaponToRegister);
	//Adding Gameplay Tag & its corresponding Weapon in the TMap
	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);
	
	//Binding fxns to custom delegate
	InWeaponToRegister->OnWeaponHit.BindUObject(this, &ThisClass::OnHitTarget);
	InWeaponToRegister->OnWeaponPulled.BindUObject(this, &ThisClass::OnAfterHitPulled);

	//If true, then equip the weapon for the given tag
	if (bRegisterAsEquippedWeapon)
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
}

AMyBaseWeapon* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if(CharacterCarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		if (AMyBaseWeapon* const* WeaponFound = CharacterCarriedWeaponMap.Find(InWeaponTagToGet))
		{
			return *WeaponFound;
		}
	}
	return nullptr;
}

AMyBaseWeapon* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if(!CurrentEquippedWeaponTag.IsValid())
		return nullptr;
	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

void UPawnCombatComponent::BP_SetWeaponCollision(bool bShouldEnable, EToggleWeaponType ToggleDamageType)
{
	if (ToggleDamageType == EToggleWeaponType::CurrentEquippedWeapon)
	{
		AMyBaseWeapon* FoundWeapon = GetCharacterCurrentEquippedWeapon();
		check(FoundWeapon);

		if (bShouldEnable) { FoundWeapon->ReturnWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly); }

		else
		{
			FoundWeapon->ReturnWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			OverlappedActors.Empty();
		}
	}
}

//Callback fxns for custom delegate, overriden in child classes.
void UPawnCombatComponent::OnHitTarget(AActor* HitActor)
{

}

void UPawnCombatComponent::OnAfterHitPulled(AActor* ActorHit)
{

}

