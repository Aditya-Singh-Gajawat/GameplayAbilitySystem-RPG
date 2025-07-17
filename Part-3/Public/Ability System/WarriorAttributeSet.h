// Aditya Singh Gajawat All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Ability System/WarriorAbilitySystemComponent.h"
#include "WarriorAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()

class GAS_RPG_API UWarriorAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UWarriorAttributeSet();

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, CurrentHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Stamina")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, MaxStamina)

	UPROPERTY(BlueprintReadOnly, Category = "Stamina")
	FGameplayAttributeData CurrentStamina;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, CurrentStamina)
	
	UPROPERTY(BlueprintReadOnly, Category = "Charged")
	FGameplayAttributeData MaxCharged;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, MaxCharged)

	UPROPERTY(BlueprintReadOnly, Category = "Charged")
	FGameplayAttributeData CurrentCharged;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, CurrentCharged)


	UPROPERTY(BlueprintReadOnly, Category = "Offense")
	FGameplayAttributeData AttackStrength;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, AttackStrength)

	UPROPERTY(BlueprintReadOnly, Category = "Defense")
	FGameplayAttributeData DefenseStrength;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, DefenseStrength)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, DamageTaken)
};
