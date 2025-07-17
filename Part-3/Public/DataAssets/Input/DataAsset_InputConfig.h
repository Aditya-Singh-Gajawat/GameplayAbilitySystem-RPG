// Aditya Singh Gajawat All Rights Reserved
#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include <GameplayTagContainer.h>
#include "DataAsset_InputConfig.generated.h"

class UInputAction; //Remember to Add InputAction module in build.cs file. 
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FWarriorInputActionConfig
{
	GENERATED_BODY() //Helps in compiling
public:
	//Allows tag which starts with InputTag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag")) 
	FGameplayTag InputTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputAction;

	bool IsValid() const
	{
		return InputTag.IsValid() && InputAction;
	}

};

UCLASS()
class GAS_RPG_API UDataAsset_InputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	//Variables
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FWarriorInputActionConfig> NativeInputActions;


	/*Binds Tags to InputActions*/
	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag) const;

	/*Doesn't need a helper function like NativeInputActions*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FWarriorInputActionConfig> AbilityInputActions;
};
