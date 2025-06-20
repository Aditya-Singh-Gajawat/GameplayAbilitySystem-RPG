// Aditya Singh Gajawat All Rights Reserved


#include "Characters/WarriorBaseCharacter.h"
#include "Ability System/WarriorAttributeSet.h"
#include "Ability System/WarriorAbilitySystemComponent.h"
// Sets default values
AWarriorBaseCharacter::AWarriorBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	GetMesh()->bReceivesDecals = false;

	AbilitySystemComponent = CreateDefaultSubobject<UWarriorAbilitySystemComponent>(TEXT("WarriorAbilitySystemComponent"));
	ASC_AttributeSet = CreateDefaultSubobject<UWarriorAttributeSet>(TEXT("Attribute-Set"));
	AbilitySystemComponent->AddAttributeSetSubobject(ASC_AttributeSet);
}

/*It gets the AbilitySystemComponent for under the hood functionality maintaining*/
UAbilitySystemComponent* AWarriorBaseCharacter::GetAbilitySystemComponent() const
{
	return ReturnWarriorAbilitySystemComponent();
}

/*This is a perfect place to initialize player-specific or controller-dependent logic, like AbilitySystemComponent*/
/*Key Point: The AbilitySystemComponent depends on OwnerActor (Controller) and AvatarActor (Pawn). So you MUST wait until possession happens to finish setting it up.*/
void AWarriorBaseCharacter::PossessedBy(AController* NewController) 
{
	Super::PossessedBy(NewController);
	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this); 
		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
	}
}


