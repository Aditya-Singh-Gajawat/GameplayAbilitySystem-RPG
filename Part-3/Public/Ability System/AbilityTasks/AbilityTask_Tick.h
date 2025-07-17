// Aditya Singh Gajawat All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_Tick.generated.h"

//Blueprints assignable deleagates for output pins!
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityTickDelegate, float, DeltaTime);
/**
 * 
 */
UCLASS()
class GAS_RPG_API UAbilityTask_Tick : public UAbilityTask
{
	GENERATED_BODY()
public:
	UAbilityTask_Tick();

	UFUNCTION(BlueprintCallable, meta = (HidePin = "OwnAbility", DefaultToSelf = "OwnAbility", BlueprintInternalUseOnly = "true"))
	static UAbilityTask_Tick* ExecutableTick(UGameplayAbility* OwnAbility);

	//~Begin UGameplayTask Interface
	virtual void TickTask(float DeltaTime) override;
	//~End UGameplayTask Interface

	UPROPERTY(BlueprintAssignable)
	FOnAbilityTickDelegate OnAbilityTick;
};
