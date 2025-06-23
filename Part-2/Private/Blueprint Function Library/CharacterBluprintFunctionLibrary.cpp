// Aditya Singh Gajawat All Rights Reserved


#include "Blueprint Function Library/CharacterBluprintFunctionLibrary.h"
#include "Interfaces/PawnCombatInterface.h"

UPawnCombatComponent* UCharacterBluprintFunctionLibrary::NativeGetCombatComponentFromActor(AActor* InActor)
{
    if(IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
    {
        return PawnCombatInterface->Interface_ReturnPawnCombatComponent();
    }
    return nullptr;
}

UPawnCombatComponent* UCharacterBluprintFunctionLibrary::BP_GetCombatComponentFromActor(AActor* InActor, EValid& OutValidCheck)
{
    UPawnCombatComponent* PawnCombatComponent =  NativeGetCombatComponentFromActor(InActor);
    OutValidCheck = PawnCombatComponent ? EValid::Valid : EValid::InValid;
    return PawnCombatComponent;
}
