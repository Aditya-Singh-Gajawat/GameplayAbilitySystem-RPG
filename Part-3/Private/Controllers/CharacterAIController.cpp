// Aditya Singh Gajawat All Rights Reserved


#include "Controllers/CharacterAIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "WarriorDebugHelper.h"

// NOTE: The base AIController already includes a perception component (PerceptionComponent).
// However, it’s not instantiated by default — so we create and configure it manually in our constructor.
// We override the default PathFollowingComponent with CrowdFollowingComponent to enable advanced crowd navigation (e.g., detour avoidance).
//To those who are interested, I've discovered that the AI controller base class already has a perception system component declared (helpfully named PerceptionSystemComponent). I could be wrong here, but I'm not seeing that it's actually instantiated in the cpp file, however. If that's the case, obviously you would definitely want to do that in your derived class's constructor!

ACharacterAIController::ACharacterAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("EnemyAISenseConfig_Sight"));
	AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
	AISenseConfig_Sight->SightRadius = 5000.f;
	AISenseConfig_Sight->LoseSightRadius = 0.f;
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = 360.f;

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("EnemyAIPerceptionComponent"));
	AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
	//When your AI has multiple senses active (e.g., Sight, Hearing, Damage), it might detect the same actor with more than one sense. Which sense should I trust the most when handling perception events or choosing targets?
	AIPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ACharacterAIController::OnEnemyPerceptionUpdated);
	//Sets Enemy AI's GenericTeamId to 1
	SetGenericTeamId(FGenericTeamId(1));
}

void ACharacterAIController::BeginPlay()
{
	// Call the base class BeginPlay to ensure default initialization occurs.
	Super::BeginPlay();
	
	// Attempt to cast the default path following component to a UCrowdFollowingComponent.
	// This allows us to access and configure advanced crowd simulation settings.
	
	if(UCrowdFollowingComponent* CrowdComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		// Enable or disable crowd simulation based on the user-defined boolean. Only enables or disables the Detour crowd simulation
		CrowdComponent->SetCrowdSimulationState(bEnabledDetourCrowdPathFollowing? ECrowdSimulationState::Enabled : ECrowdSimulationState::Disabled);
		
		// Set the crowd avoidance quality based on the configured integer value.
		// This affects how smart and costly the avoidance behavior will be.
		switch (DetourCrowdAvoidanceQuality)
		{
			case 1: CrowdComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low); break;
			case 2: CrowdComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium); break;
			case 3: CrowdComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good); break;
			case 4: CrowdComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High); break;
			default: // Do nothing if the value is not within the expected range. 
				break;
		}

		// Assign this AI character to avoidance group 1.3
		// Used for defining what groups it belongs to during avoidance checks.
		CrowdComponent->SetAvoidanceGroup(1);

		// Specify which groups this AI should avoid (in this case, group 1).
		CrowdComponent->SetGroupsToAvoid(1);

		// Set the range at which this character starts detecting potential collisions with others.
		CrowdComponent->SetCrowdCollisionQueryRange(CollisionQueryRange);
	}
}

ETeamAttitude::Type ACharacterAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	//Casting to Pawn
	const APawn* PawnInCheck = Cast<const APawn>(&Other);
	//Casting to Pawn's Controller to check if it implements IGenericTeamAgentInterface interface. That's where we will set player's or casted pawn's GenericTeamId.
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(PawnInCheck->GetController());
	//If OtherTeamAgent's GenericTeamId is not equal to (this) Enemy Generic Team Id then OtherTeamAgent is hostile, otherwise, it is friendly. 
	if(OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() < GetGenericTeamId())
	{
		return ETeamAttitude::Hostile;
	}
	return ETeamAttitude::Friendly;
}

//Whenever enemy detects hostile pawn this function will be called!
void ACharacterAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if(UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		if(!BlackboardComponent->GetValueAsObject(FName("TargetActor")))
		{
			if (Stimulus.WasSuccessfullySensed() && Actor)
			{
				BlackboardComponent->SetValueAsObject(FName("TargetActor"), Actor);
			}
		}
	}
}