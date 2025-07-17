// Aditya Singh Gajawat All Rights Reserved


#include "AnimInstances/Warrior/MyWarriorHeroAnimInstance.h"
#include "Characters/MyWarriorHeroCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyWarriorHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	OwningCharacter = Cast<AMyWarriorHeroCharacter>(TryGetPawnOwner());
}

void UMyWarriorHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	if (!OwnerCharacter) return;
	if (bIsAccerelating) 
	{
		IdleEmotesTimer = 0.f;
		bCanPlayEmotes = false;
	}
	IdleEmotesTimer += DeltaSeconds;
	bCanPlayEmotes = (IdleEmotesTimer >= IdleEmotesThreshold);
}
