// Aditya Singh Gajawat All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WarriorBaseAnimInstance.h"
#include "MyWarriorHeroLinkedAnimInstance.generated.h"

class UMyWarriorHeroAnimInstance;

UCLASS()
class GAS_RPG_API UMyWarriorHeroLinkedAnimInstance : public UWarriorBaseAnimInstance
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	UMyWarriorHeroAnimInstance* GetAnimInstance() const;
};
