// Aditya Singh Gajawat All Rights Reserved
#pragma once
#include "CoreMinimal.h"
#include "Characters/WarriorBaseCharacter.h"
#include <GameplayTagContainer.h>
#include "MyWarriorHeroCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
struct FInputActionValue;
class UHeroCombatComponent;

UCLASS()
class GAS_RPG_API AMyWarriorHeroCharacter : public AWarriorBaseCharacter
{
	GENERATED_BODY()
public:
	AMyWarriorHeroCharacter();
protected:
	//~ Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
	
	//~ Begin IPawnCombatInterface Interface
	virtual UPawnCombatComponent* Interface_ReturnPawnCombatComponent() override;
	//~ End IPawnCombatInterface Interface

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Basic Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, Category = "Basic Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, Category = "Basic Components", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic Components", meta = (AllowPrivateAccess = "true"))
	UHeroCombatComponent* HeroCombatComponent;

	int OutLightComboCounter = 0;
	int OutHeavyComboCounter = 0;

#pragma region Inputs
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);
	
	UFUNCTION(BlueprintCallable)
	void GetLightComboCounterValueForActor(int InComboCounter);
	UFUNCTION(BlueprintCallable)
	void GetHeavyComboCounterValueForActor(int InComboCounter);
#pragma endregion
public:
	FORCEINLINE UHeroCombatComponent* ReturnMyHeroCombatComponent() const { return HeroCombatComponent; }
	FORCEINLINE USpringArmComponent* ReturnMySpringArmComponent() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* ReturnMyFollowCameraComponent() const { return FollowCamera; }
	FORCEINLINE int ReturnMyHeroLightAttackComboCounter() const { return OutLightComboCounter; }
	FORCEINLINE int ReturnMyHeroHeavyAttackComboCounter() const { return OutHeavyComboCounter; }
};
