// Aditya Singh Gajawat All Rights Reserved


#include "Components/Combat/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTag/MyGameplayTags.h"
#include "Blueprint Function Library/CharacterBluprintFunctionLibrary.h"

#include "WarriorDebugHelper.h"

void UEnemyCombatComponent::OnHitTarget(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}

	OverlappedActors.AddUnique(HitActor);

	//TODO:: Implement block check
	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = UCharacterBluprintFunctionLibrary::NativeDoesActorHaveTag(HitActor, WarriorGameplayTags::Player_Status_Block);
	const bool bIsMyAttackUnblockable = false;

	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		bIsValidBlock = UCharacterBluprintFunctionLibrary::CheckForValidBlock(HitActor, GetOwningPawn());
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;

	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor
		(
			HitActor,
			WarriorGameplayTags::Player_Event_BlockSuccess,
			EventData
		);
	}
	else
	{
		if(bIsPlayerBlocking && !bIsMyAttackUnblockable)
		{
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor
			(
				HitActor,
				WarriorGameplayTags::Player_Event_BlockFailed,
				EventData
			);
		}
		else
		{
			Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + " Hits " + HitActor->GetActorNameOrLabel());
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor
			(
				GetOwningPawn(),
				WarriorGameplayTags::Shared_Event_RegisterHit,
				EventData
			);
		}
    }
}




