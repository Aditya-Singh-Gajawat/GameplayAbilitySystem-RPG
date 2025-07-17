// Aditya Singh Gajawat All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTag/MyGameplayTags.h"
#include "CharacterBluprintFunctionLibrary.generated.h"

class UWarriorAbilitySystemComponent;
class UPawnCombatComponent;

UENUM()
enum class EValid : uint8
{
	Valid,
	InValid
};

UENUM()
enum class EWarriorConfirmType : uint8
{
	Yes,
	No
};

UCLASS()
class GAS_RPG_API UCharacterBluprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static UWarriorAbilitySystemComponent* NativeGetWarriorASCFromActor(AActor* InActor);
	
	UFUNCTION(BlueprintCallable)
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = "Warrior|FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EWarriorConfirmType& OutConfirmType);

	UFUNCTION(BlueprintCallable)
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	static UPawnCombatComponent* NativeGetCombatComponentFromActor(AActor* InActor);
	
	UFUNCTION(BlueprintCallable, Category = "CharacterBlueprintFunctionLibrary", meta = (DisplayName = "GetPawnCombatComponentPerActor", ExpandEnumAsExecs = "OutValidCheck"))
	static UPawnCombatComponent* BP_GetCombatComponentFromActor(AActor* InActor, EValid& OutValidCheck);

	UFUNCTION(BlueprintCallable)
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintPure)
	static FGameplayTag ComputeHitReactDirectionForATag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference);

	UFUNCTION(BlueprintPure)
	static bool CheckForValidBlock(AActor* InDefender, AActor* InAttacker);
};
