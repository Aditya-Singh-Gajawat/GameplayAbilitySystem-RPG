// Aditya Singh Gajawat All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "HeroCombatComponent.generated.h"

class AMyHeroWeapon;

UCLASS()
class GAS_RPG_API UHeroCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	AMyHeroWeapon* GetHeroCarriedWeaponByTag (FGameplayTag InWeaponTag);
};
