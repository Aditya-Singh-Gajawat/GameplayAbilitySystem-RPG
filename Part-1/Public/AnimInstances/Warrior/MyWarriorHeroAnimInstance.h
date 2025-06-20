// Aditya Singh Gajawat All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/MyWarriorCharacterAnimInstance.h"
#include "MyWarriorHeroAnimInstance.generated.h"

class AMyWarriorHeroCharacter;
class UCharacterMovementComponent;

UCLASS()
class GAS_RPG_API UMyWarriorHeroAnimInstance : public UMyWarriorCharacterAnimInstance
{
	GENERATED_BODY()
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
	UPROPERTY(BlueprintReadOnly)
	AMyWarriorHeroCharacter* OwningCharacter;
private:
	float IdleEmotesTimer;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Properties|Parameters", meta = (AllowPrivateAccess = "true"))
	float IdleEmotesThreshold = 15.f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Animation Properties|Parameters", meta = (AllowPrivateAccess = "true"))
	bool bCanPlayEmotes;
};
