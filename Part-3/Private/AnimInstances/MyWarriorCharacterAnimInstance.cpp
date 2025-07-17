// Aditya Singh Gajawat All Rights Reserved


#include "AnimInstances/MyWarriorCharacterAnimInstance.h"
#include "Characters/WarriorBaseCharacter.h"
#include "KismetAnimationLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayTag/MyGameplayTags.h"
#include "Blueprint Function Library/CharacterBluprintFunctionLibrary.h"


void UMyWarriorCharacterAnimInstance::NativeInitializeAnimation()
{
	OwnerCharacter = Cast<AWarriorBaseCharacter>(TryGetPawnOwner());
	if (OwnerCharacter) 
	{
		OwnerCharacterMovement = OwnerCharacter->GetCharacterMovement();
	}
}

void UMyWarriorCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwnerCharacter && !OwnerCharacterMovement) return;

	GroundSpeed = OwnerCharacter->GetVelocity().Size2D();
	bIsAccerelating = OwnerCharacterMovement->GetCurrentAcceleration().SizeSquared2D() > 0.f; 
	StrafeDirection = UKismetAnimationLibrary::CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetActorRotation());
	bIsFalling = OwnerCharacter->GetCharacterMovement()->IsFalling();
}
