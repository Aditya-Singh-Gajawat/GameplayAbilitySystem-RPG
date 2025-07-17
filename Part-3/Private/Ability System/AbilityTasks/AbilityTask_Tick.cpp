// Aditya Singh Gajawat All Rights Reserved


#include "Ability System/AbilityTasks/AbilityTask_Tick.h"

UAbilityTask_Tick::UAbilityTask_Tick()
{
	bTickingTask = true;
}

UAbilityTask_Tick* UAbilityTask_Tick::ExecutableTick(UGameplayAbility* OwnAbility)
{
	UAbilityTask_Tick* Node = NewAbilityTask<UAbilityTask_Tick>(OwnAbility);
	return Node;
}

void UAbilityTask_Tick::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnAbilityTick.Broadcast(DeltaTime);
	}
	else
	{
		EndTask();
	}
}
