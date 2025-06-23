// Aditya Singh Gajawat All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEExec_DamageTaken.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API UGEExec_DamageTaken : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UGEExec_DamageTaken();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
