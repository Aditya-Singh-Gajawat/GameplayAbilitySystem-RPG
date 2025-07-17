// Aditya Singh Gajawat All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/MyWarriorHeroGameplayAbility.h"
#include "HeroGameplayAbility_ToggleTarget.generated.h"

class UUserWidget;
/**
 * 
 */
UCLASS()
class GAS_RPG_API UHeroGameplayAbility_ToggleTarget : public UMyWarriorHeroGameplayAbility
{
	GENERATED_BODY()

protected:
	//~ Begin UGameplayAbility Interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface

	UFUNCTION(BlueprintCallable)
	void OnTick_Target(float DeltaTime);

private:
	void TryToLockOnTheTarget();
	AActor* GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors);
	void GetAvailableActors();
	void CancelTargetLockAbility();
	void CleanUp();
	void DrawTargetWidget();
	void SetDrawnWidgetPosition();
	void SetLockTargetMovementSpeed();
	void ResetLockTargetMovementSpeed();

	UPROPERTY(EditDefaultsOnly)
	float TraceDistance = 3000.f;
	UPROPERTY(EditDefaultsOnly)
	FVector TraceBoxSize = FVector(5000.f, 5000.f, 300.f);
	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> BoxTraceChannel;
	UPROPERTY(EditDefaultsOnly)
	bool bShowPersistentDebugShape = false;
	UPROPERTY(EditDefaultsOnly)
	float SetTargetLockMovementSpeed = 275.f;
	
	UPROPERTY()
	TArray<AActor*> AvailableActorsToLock;
	UPROPERTY()
	AActor* ActorToLockOn;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> TargetAimWidgetClass;
	UPROPERTY()
	UUserWidget* DrawnWidget;
	UPROPERTY()
	FVector2D TargetLockWidgetSize = FVector2D::ZeroVector;
	UPROPERTY()
	float CachedMovementSpeed = 0.f;
};
