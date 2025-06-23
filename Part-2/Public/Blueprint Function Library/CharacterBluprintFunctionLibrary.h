// Aditya Singh Gajawat All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CharacterBluprintFunctionLibrary.generated.h"

class UPawnCombatComponent;

UENUM()
enum class EValid : uint8
{
	Valid,
	InValid
};

UCLASS()
class GAS_RPG_API UCharacterBluprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static UPawnCombatComponent* NativeGetCombatComponentFromActor(AActor* InActor);
	UFUNCTION(BlueprintCallable, Category = "CharacterBlueprintFunctionLibrary", meta = (DisplayName = "GetPawnCombatComponentPerActor", ExpandEnumAsExecs = "OutValidCheck"))
	static UPawnCombatComponent* BP_GetCombatComponentFromActor(AActor* InActor, EValid& OutValidCheck);
};
