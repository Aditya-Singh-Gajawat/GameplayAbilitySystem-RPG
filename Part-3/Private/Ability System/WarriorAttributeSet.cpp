// Aditya Singh Gajawat All Rights Reserved


#include "Ability System/WarriorAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Blueprint Function Library/CharacterBluprintFunctionLibrary.h"
#include "GameplayTag/MyGameplayTags.h"

#include "WarriorDebugHelper.h"

UWarriorAttributeSet::UWarriorAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentStamina(1.f);
	InitMaxStamina(1.f);
	InitCurrentCharged(1.f);
	InitMaxCharged(1.f);
	InitAttackStrength(1.f);
	InitDefenseStrength(1.f);
}

void UWarriorAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if(Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);
	}
	if(Data.EvaluatedData.Attribute == GetCurrentChargedAttribute())
	{
		const float NewCurrentCharged = FMath::Clamp(GetCurrentCharged(), 0.f, GetMaxCharged());
		SetCurrentCharged(NewCurrentCharged);
	}
	if(Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float Damage = GetDamageTaken();
		const float NewCurrentHealth = FMath::Clamp(OldHealth - Damage, 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);
		const FString DebugString = FString::Printf
		(
			TEXT("Old Health : %f, Damage Done: %f, NewCurrentHealth: %f"),
			OldHealth,
			Damage,
			NewCurrentHealth
		);

		Debug::Print(DebugString, FColor::Magenta);
		
		//TODO::Handle UI
		
		if (NewCurrentHealth == 0.f)
		{
			UCharacterBluprintFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), WarriorGameplayTags::Shared_Status_Death);
		}
	}
}
