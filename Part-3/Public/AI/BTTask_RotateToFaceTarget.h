// Aditya Singh Gajawat All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RotateToFaceTarget.generated.h"

struct FRotateToFaceTargetTaskMemory
{
	TWeakObjectPtr<APawn> OwningPawn;
	TWeakObjectPtr<AActor> TargetActor;

	bool IsValid() const
	{
		return OwningPawn.IsValid() && TargetActor.IsValid();
	}
	
	void Reset()
	{
		//Resets weak pointer back to nullptr
		OwningPawn.Reset();
		TargetActor.Reset();
	}
};
/**
 * 
 */
UCLASS()
class GAS_RPG_API UBTTask_RotateToFaceTarget : public UBTTaskNode
{
	GENERATED_BODY()

	UBTTask_RotateToFaceTarget();

	//~Begin UBTNode Interface.
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual uint16 GetInstanceMemorySize() const override;
	virtual FString GetStaticDescription() const override;
	//~End UBTNode Interface.

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	bool HasReachedAnglePrecision(APawn* QueryPawn, AActor* TargetActor) const;

	UPROPERTY(EditAnywhere, Category = "Facing Target")
	float AnglePrecision;
	UPROPERTY(EditAnywhere, Category = "Facing Target")
	float RotationInterpSpeed;
	UPROPERTY(EditAnywhere, Category = "Facing Target")
	FBlackboardKeySelector InTargetActorKey;
};
