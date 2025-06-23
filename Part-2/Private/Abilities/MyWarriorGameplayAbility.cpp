// Aditya Singh Gajawat All Rights Reserved


#include "Abilities/MyWarriorGameplayAbility.h"
#include "Ability System/WarriorAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

/*Called when the ability is given to an AbilitySystemComponent*/
void UMyWarriorGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	if(AbilityActivationPolicy == EAbilityActivationPolicy::OnGiven)
	{	/*Native function, called if an ability ends normally or abnormally.*/
		/*If ActorInfo is valid && the gameplay ability is not active, then do*/
		if(ActorInfo && !Spec.IsActive())
		{
			/*Activates the ability right away as the abilities will be of OnGiven policy type*/
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle); 
		}
	}
}

/*Native function, called if an ability ends normally or abnormally.*/
void UMyWarriorGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	if(AbilityActivationPolicy == EAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UPawnCombatComponent* UMyWarriorGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	//Iterates through all the UPawnCombatComponent based class for the character and castes to it.
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

UWarriorAbilitySystemComponent* UMyWarriorGameplayAbility::GetWarriorAbilitySystemComponentFromActorInfo() const
{
	return Cast<UWarriorAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FActiveGameplayEffectHandle UMyWarriorGameplayAbility::NativeGiveEffectSpecHandleToTarget(AActor* Target, const FGameplayEffectSpecHandle& InSpecHandle)
{
	UAbilitySystemComponent* TargetASC =  UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	check(TargetASC && InSpecHandle.IsValid());
	
	return GetWarriorAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget
	(
		*InSpecHandle.Data,
		TargetASC
	);
}

FActiveGameplayEffectHandle UMyWarriorGameplayAbility::BP_GiveEffectSpecHandleToTarget(AActor* Target, const FGameplayEffectSpecHandle& InSpecHandle, EBaseCharactersSuccess& OutSuccessType)
{
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeGiveEffectSpecHandleToTarget(Target, InSpecHandle);
	OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? EBaseCharactersSuccess::Successed : EBaseCharactersSuccess::Failed;

	return ActiveGameplayEffectHandle;
}


