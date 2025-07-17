// Aditya Singh Gajawat All Rights Reserved


#include "Characters/MyEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "Engine/AssetManager.h"
#include "DataAssets/StartUpData/MyDataAsset_EnemyStartUpData.h"

#include "WarriorDebugHelper.h"


void AMyEnemyCharacter::InitializeEnemyStartUpDataAsset()
{
	if (CharacterStartUpData.IsNull()) return;
	UAssetManager::GetStreamableManager().RequestAsyncLoad
	(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if(UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(AbilitySystemComponent);
					//Debug::Print(TEXT("Enemy start up data loaded"));
				}
			}
		)
	);
}

AMyEnemyCharacter::AMyEnemyCharacter()
{
	//Ensures haaving functional AI when spawned in the world
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned; 
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 100.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("Enemy Combat Component"));
}

UPawnCombatComponent* AMyEnemyCharacter::Interface_ReturnPawnCombatComponent()
{
	return EnemyCombatComponent;
}

void AMyEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitializeEnemyStartUpDataAsset();
}
