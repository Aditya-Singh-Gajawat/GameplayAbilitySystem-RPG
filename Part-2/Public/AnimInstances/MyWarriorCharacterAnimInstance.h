// Aditya Singh Gajawat All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WarriorBaseAnimInstance.h"
#include "MyWarriorCharacterAnimInstance.generated.h"

class AWarriorBaseCharacter;
class UCharacterMovementComponent;
UCLASS()
class GAS_RPG_API UMyWarriorCharacterAnimInstance : public UWarriorBaseAnimInstance
{
	GENERATED_BODY()
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	//Don't declare a raw pointer without associating it with an UPROPERTY as to allow it be a garbage collection.
	UPROPERTY() 
	AWarriorBaseCharacter* OwnerCharacter;
	UPROPERTY()
	UCharacterMovementComponent* OwnerCharacterMovement;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Animation Properties|Parameters")
	float GroundSpeed;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Animation Properties|Parameters")
	bool bIsAccerelating;
public:
};
