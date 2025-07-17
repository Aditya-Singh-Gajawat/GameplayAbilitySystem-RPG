// Aditya Singh Gajawat All Rights Reserved


#include "GEExec/GEExec_DamageTaken.h"
#include "Ability System/WarriorAttributeSet.h"
#include "GameplayTag/MyGameplayTags.h"

#include "WarriorDebugHelper.h"

//Method - 1 
struct FCharacterDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackStrength)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefenseStrength)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)
	FCharacterDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet, AttackStrength, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet, DefenseStrength, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet, DamageTaken, Target, false)
	}
};

static const FCharacterDamageCapture& GetCharacterDamageCapture()
{
	static FCharacterDamageCapture CharacterDamageCapture;
	return CharacterDamageCapture;
}

UGEExec_DamageTaken::UGEExec_DamageTaken()
{
	//Method - 2
	/*FProperty* AttackStrengthProperty = FindFieldChecked<FProperty>(
		UWarriorAttributeSet::StaticClass(),
		GET_MEMBER_NAME_CHECKED(UWarriorAttributeSet, AttackStrength)
	);

	FGameplayEffectAttributeCaptureDefinition AttackStrengthCaptureDefinition
	(
		AttackStrengthProperty,
		EGameplayEffectAttributeCaptureSource::Source,
		false
	);

	FProperty* DefenseStrengthProperty = FindFieldChecked<FProperty>(
		UWarriorAttributeSet::StaticClass(),
		GET_MEMBER_NAME_CHECKED(UWarriorAttributeSet, DefenseStrength)
	);
	
	FGameplayEffectAttributeCaptureDefinition DefenseStrengthCaptureDefinition
	(
		DefenseStrengthProperty,
		EGameplayEffectAttributeCaptureSource::Target,
		false
	);*/

	//Method - 1 
	RelevantAttributesToCapture.Add(GetCharacterDamageCapture().AttackStrengthDef);
	RelevantAttributesToCapture.Add(GetCharacterDamageCapture().DefenseStrengthDef);
	RelevantAttributesToCapture.Add(GetCharacterDamageCapture().DamageTakenDef);

	//Method - 2
	/*RelevantAttributesToCapture.Add(AttackStrengthCaptureDefinition);
	RelevantAttributesToCapture.Add(DefenseStrengthCaptureDefinition);*/
}

void UGEExec_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	//EffectSpec.GetContext().GetSourceObject();
	//EffectSpec.GetContext().GetInstigator();
	//EffectSpec.GetContext().GetAbility();
	//EffectSpec.GetContext().GetEffectCauser();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();

	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackStrength = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude
	(
		GetCharacterDamageCapture().AttackStrengthDef,
		EvaluateParameters,
		SourceAttackStrength
	);
	//Debug::Print(TEXT("SourceAttackStrength"), SourceAttackStrength);

	float BaseDamage = 0.f;
	int32 UsedLightAttackComboCount = 0;
	int32 UsedHeavyAttackComboCount = 0;

	for(const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if(TagMagnitude.Key.MatchesTagExact(WarriorGameplayTags::Shared_EffectSpec_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			//Debug::Print(TEXT("BaseDamage"), BaseDamage);
		}
		if(TagMagnitude.Key.MatchesTagExact(WarriorGameplayTags::Player_Effect_Attack_Light))
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
			//Debug::Print(TEXT("UsedLightAttackComboCount"), UsedLightAttackComboCount);
		}
		if(TagMagnitude.Key.MatchesTagExact(WarriorGameplayTags::Player_Effect_Attack_Heavy))
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
			//Debug::Print(TEXT("UsedHeavyAttackComboCount"), UsedHeavyAttackComboCount);
		}
	}

	float TargetDefenseStrength = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude
	(
		GetCharacterDamageCapture().DefenseStrengthDef,
		EvaluateParameters,
		TargetDefenseStrength
	);
	//Debug::Print(TEXT("TargetDefenseStrength"), TargetDefenseStrength);

	//Calculating Final Damage 
	if(UsedLightAttackComboCount != 0)
	{
		const float DamageIncreasePercentLight = (UsedLightAttackComboCount - 1) * 0.05 + 1.f;
		BaseDamage *= DamageIncreasePercentLight;
		//Debug::Print(TEXT("ScaledBaseDamageLight"), BaseDamage);
	}

	if(UsedHeavyAttackComboCount != 0)
	{
		const float DamageIncreasePercentHeavy = UsedHeavyAttackComboCount * 0.15f + 1.f;
		BaseDamage *= DamageIncreasePercentHeavy;
		//Debug::Print(TEXT("ScaledBaseDamageHeavy"), BaseDamage);
	}

	const float FinalDamage = BaseDamage * SourceAttackStrength / TargetDefenseStrength;
	Debug::Print(TEXT("FinalDamage"), FinalDamage);
	if(FinalDamage > 0.f)
	{
		//We don't modify CurrentHealth attribute directly rather we modify placeholder attribute
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetCharacterDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamage
			)
		);
	}
}


