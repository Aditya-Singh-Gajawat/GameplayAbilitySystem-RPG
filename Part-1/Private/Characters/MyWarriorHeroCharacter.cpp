// Aditya Singh Gajawat All Rights Reserved

#include "Characters/MyWarriorHeroCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "Components/Input/WarriorInputComponent.h"
#include "GameplayTag/MyGameplayTags.h"
#include "DataAssets/StartUpData/DataAsset_HeroStartUpData.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "Ability System/WarriorAbilitySystemComponent.h"

#include "GAS_RPG/Public/WarriorDebugHelper.h"

AMyWarriorHeroCharacter::AMyWarriorHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);  // Set the size of the character's collision capsule (width = 42, height = 96)

	bUseControllerRotationPitch = false;  // Don't rotate the character up/down with the controller
	bUseControllerRotationRoll = false;   // Don't roll the character with the controller
	bUseControllerRotationYaw = false;    // Don't turn the character left/right with the controller

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));  // Create the spring arm (camera boom) to hold the camera
	CameraBoom->SetupAttachment(GetRootComponent());  // Attach the boom to the character's root (usually the capsule)
	CameraBoom->TargetArmLength = 250.f;  // Set how far behind the camera should be from the character
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);  // Offset the camera slightly to the side and above the character
	CameraBoom->bUsePawnControlRotation = true;  // Make the boom rotate based on controller input (e.g., mouse or right stick)

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));  // Create the camera component
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);  // Attach the camera to the end of the spring arm
	FollowCamera->bUsePawnControlRotation = false;  // Don't rotate the camera on its own, it follows the boom's rotation

	GetCharacterMovement()->bOrientRotationToMovement = true;  // Make the character rotate in the direction of movement
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);  // Set how fast the character can turn
	GetCharacterMovement()->MaxWalkSpeed = 400.f;  // Set the walking speed of the character
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;  // Set how quickly the character slows down and stops when input is released

	HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombatComponent"));
}

void AMyWarriorHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if(!CharacterStartUpData.IsNull())
	{
		if(UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(AbilitySystemComponent);
		}
	}
}

void AMyWarriorHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(InputConfigDataAsset);

	//Add mapping context
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);
	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
	UWarriorInputComponent* WarriorInputComponent =  CastChecked<UWarriorInputComponent>(PlayerInputComponent);

	WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &AMyWarriorHeroCharacter::Input_Move);
	WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &AMyWarriorHeroCharacter::Input_Look);

	WarriorInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &AMyWarriorHeroCharacter::Input_AbilityInputPressed, &AMyWarriorHeroCharacter::Input_AbilityInputReleased);
}

void AMyWarriorHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}


void AMyWarriorHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	if(MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}
	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMyWarriorHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	if (LookAxisVector.X != 0.f)
		AddControllerYawInput(LookAxisVector.X);
	if (LookAxisVector.Y != 0.f)
		AddControllerPitchInput(LookAxisVector.Y);
}

void AMyWarriorHeroCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	AbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void AMyWarriorHeroCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	AbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}
