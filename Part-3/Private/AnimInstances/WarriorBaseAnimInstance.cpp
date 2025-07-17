// Aditya Singh Gajawat All Rights Reserved


#include "AnimInstances/WarriorBaseAnimInstance.h"
#include "Blueprint Function Library/CharacterBluprintFunctionLibrary.h"

bool UWarriorBaseAnimInstance::DoesOwnerHasTag(FGameplayTag InTagToCheck) const
{
    if(APawn* OwningPawn = TryGetPawnOwner())
    {
       return UCharacterBluprintFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, InTagToCheck);
    }
    return false;
}
