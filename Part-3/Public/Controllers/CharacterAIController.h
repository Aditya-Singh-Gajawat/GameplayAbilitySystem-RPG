// Aditya Singh Gajawat All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CharacterAIController.generated.h"


class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class GAS_RPG_API ACharacterAIController : public AAIController
{
	GENERATED_BODY()
public:
	ACharacterAIController(const FObjectInitializer& ObjectInitializer);
	//~Begin IGenericTeamAgentInterface Interface.
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	//~End IGenericTeamAgentInterface Interface.
protected:
	virtual void BeginPlay() override;
	//Use UAIPerceptionComponent when you want AI to react to the world (players, noises, etc.) without writing a lot of detection code yourself.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAIPerceptionComponent* AIPerceptionComponent;

	//UAISenseConfig_Sight requires a UAIPerceptionComponent to actually function. Without UAIPerceptionComponent, your AI will not detect anything, even if you configure Sight.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAISenseConfig_Sight* AISenseConfig_Sight;

	UFUNCTION()
	virtual void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
private:
	UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Configuration")
	bool bEnabledDetourCrowdPathFollowing = true;
	UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Configuration", meta = (EditCondition = "bEnabledDetourCrowdPathFollowing", UIMin = "1", UIMax = "4"))
	int32 DetourCrowdAvoidanceQuality = 4;
	UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Configuration")
	float CollisionQueryRange = 600.f;
};
