// Aditya Singh Gajawat All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "GameplayTagContainer.h"
#include "PawnCombatComponent.generated.h"

class AMyBaseWeapon; 

UENUM(BlueprintType)
enum class EToggleWeaponType : uint8
{
	CurrentEquippedWeapon,
	left_handed,
	right_handed
};

UCLASS()
class GAS_RPG_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
protected:
	TArray<AActor*> OverlappedActors;
public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AMyBaseWeapon* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	AMyBaseWeapon* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	AMyBaseWeapon* GetCharacterCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Combat|Hit")
	void BP_SetWeaponCollision(bool bShouldEnable, EToggleWeaponType ToggleDamageType = EToggleWeaponType::CurrentEquippedWeapon);

	UPROPERTY(BlueprintReadWrite, Category = "Warrior|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	virtual void OnHitTarget(AActor* HitActor);
	virtual void OnAfterHitPulled(AActor* ActorHit);

private:
	TMap<FGameplayTag,AMyBaseWeapon*> CharacterCarriedWeaponMap;
};
