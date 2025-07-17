// Aditya Singh Gajawat All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/PawnCombatInterface.h"
#include "WarriorBaseCharacter.generated.h"

class UWarriorAbilitySystemComponent;
class UWarriorAttributeSet;
class UDataAsset_StartUpDataBase;
class UMotionWarpingComponent;

UCLASS()
class GAS_RPG_API AWarriorBaseCharacter : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface
{
	GENERATED_BODY()
public:
	AWarriorBaseCharacter();

	//~ Begin IAbilitySystemInterface Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override; 
	//~ End IAbilitySystemInterface Interface
protected:
	//~ Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
	// 
	//~ Begin IPawnCombatInterface Interface
	virtual UPawnCombatComponent* Interface_ReturnPawnCombatComponent() override;
	//~ End IPawnCombatInterface Interface

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay Ability System Components")
	UWarriorAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay Ability System Components")
	UWarriorAttributeSet* ASC_AttributeSet;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpData;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Motion Warping")
	UMotionWarpingComponent* MotionWarpingComponent;
public:
	FORCEINLINE UWarriorAbilitySystemComponent* ReturnWarriorAbilitySystemComponent() const { return AbilitySystemComponent; }
	FORCEINLINE UWarriorAttributeSet* ReturnWarriorAttributeSet() const { return ASC_AttributeSet; }
};
