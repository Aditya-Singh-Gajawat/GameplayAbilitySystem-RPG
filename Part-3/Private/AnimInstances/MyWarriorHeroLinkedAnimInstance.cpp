// Aditya Singh Gajawat All Rights Reserved


#include "AnimInstances/MyWarriorHeroLinkedAnimInstance.h"
#include "AnimInstances/Warrior/MyWarriorHeroAnimInstance.h"

UMyWarriorHeroAnimInstance* UMyWarriorHeroLinkedAnimInstance::GetAnimInstance() const
{
	//GetOwningComponent()->GetAnimInstance(), gets us owning anim instance
	return Cast<UMyWarriorHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
