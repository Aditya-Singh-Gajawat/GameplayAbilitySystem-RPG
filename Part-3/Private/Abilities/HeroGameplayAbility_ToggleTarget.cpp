// Aditya Singh Gajawat All Rights Reserved

#include "Abilities/HeroGameplayAbility_ToggleTarget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/MyWarriorHeroCharacter.h"
#include "Controllers/WarriorHeroController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/SizeBox.h"
#include "Blueprint Function Library/CharacterBluprintFunctionLibrary.h"
#include "GameplayTag/MyGameplayTags.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "WarriorDebugHelper.h"

void UHeroGameplayAbility_ToggleTarget::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	TryToLockOnTheTarget();
	SetLockTargetMovementSpeed();
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UHeroGameplayAbility_ToggleTarget::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	CleanUp();
	ResetLockTargetMovementSpeed();
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UHeroGameplayAbility_ToggleTarget::OnTick_Target(float DeltaTime)
{
	if(!ActorToLockOn || UCharacterBluprintFunctionLibrary::NativeDoesActorHaveTag(ActorToLockOn, WarriorGameplayTags::Shared_Status_Death) || UCharacterBluprintFunctionLibrary::NativeDoesActorHaveTag(GetMyWarriorHeroCharacterFromActorInfo(), WarriorGameplayTags::Shared_Status_Death))
	{
		CancelTargetLockAbility();
		return;
	}

	SetDrawnWidgetPosition();

	bool bShouldAdjustThePosition = !UCharacterBluprintFunctionLibrary::NativeDoesActorHaveTag(GetMyWarriorHeroCharacterFromActorInfo(), WarriorGameplayTags::Player_Status_IsRolling);
	if(bShouldAdjustThePosition)
	{
		const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetMyWarriorHeroCharacterFromActorInfo()->GetActorLocation(), ActorToLockOn->GetActorLocation());
		//Orient player character & camera
		const FRotator CurrentHeroRot = GetWarriorHeroControllerFromActorInfo()->GetControlRotation();
		const FRotator TargetRot = FMath::RInterpTo(CurrentHeroRot, LookAtRot, DeltaTime, 5.f); 

		GetWarriorHeroControllerFromActorInfo()->SetControlRotation(FRotator(TargetRot.Pitch, TargetRot.Yaw, 0.f));
		GetMyWarriorHeroCharacterFromActorInfo()->SetActorRotation(FRotator(0.f,TargetRot.Yaw,0.f));
	}
}

void UHeroGameplayAbility_ToggleTarget::TryToLockOnTheTarget()
{
	GetAvailableActors();
	if(AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}
	ActorToLockOn = GetNearestTargetFromAvailableActors(AvailableActorsToLock);
	if(ActorToLockOn)
	{
		DrawTargetWidget();
		SetDrawnWidgetPosition();
	}
	else
	{
		CancelTargetLockAbility();
	}
}

AActor* UHeroGameplayAbility_ToggleTarget::GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors)
{
	float ClosestDistance = 0.f;
	return UGameplayStatics::FindNearestActor(GetMyWarriorHeroCharacterFromActorInfo()->GetActorLocation(), InAvailableActors, ClosestDistance);
}

void UHeroGameplayAbility_ToggleTarget::GetAvailableActors()
{
	TArray<FHitResult> BoxTraceHits;
	UKismetSystemLibrary::BoxTraceMultiForObjects
	(
		GetMyWarriorHeroCharacterFromActorInfo(),
		GetMyWarriorHeroCharacterFromActorInfo()->GetActorLocation(),
		GetMyWarriorHeroCharacterFromActorInfo()->GetActorLocation() + GetMyWarriorHeroCharacterFromActorInfo()->GetActorForwardVector() * TraceDistance,
		TraceBoxSize / 2.f,
		GetMyWarriorHeroCharacterFromActorInfo()->GetActorForwardVector().ToOrientationRotator(),
		BoxTraceChannel,
		false,
		TArray<AActor*>(),
		bShowPersistentDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		BoxTraceHits,
		true
	);
	for(const FHitResult& TraceHit : BoxTraceHits)
	{
		if(AActor* HitActor = TraceHit.GetActor())
		{
			if(HitActor!=GetMyWarriorHeroCharacterFromActorInfo())
			{
				AvailableActorsToLock.AddUnique(HitActor);
			}
		}
	}
}

void UHeroGameplayAbility_ToggleTarget::CancelTargetLockAbility()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}

void UHeroGameplayAbility_ToggleTarget::CleanUp()
{
	AvailableActorsToLock.Empty();
	ActorToLockOn = nullptr;

	if (DrawnWidget)
		DrawnWidget->RemoveFromParent();

	DrawnWidget = nullptr;
	TargetLockWidgetSize = FVector2D::ZeroVector;
}

void UHeroGameplayAbility_ToggleTarget::DrawTargetWidget()
{
	if(!DrawnWidget)
	{
		checkf(TargetAimWidgetClass, TEXT("Didn't assigned Widget Class"));
		DrawnWidget = CreateWidget<UUserWidget>(GetWarriorHeroControllerFromActorInfo(), TargetAimWidgetClass);
		check(DrawnWidget);
		DrawnWidget->AddToViewport();
	}
}

void UHeroGameplayAbility_ToggleTarget::SetDrawnWidgetPosition()
{
	if (!DrawnWidget || !ActorToLockOn) 
	{ 
		CancelTargetLockAbility();
		return; 
	}

	FVector2D ScreenPosition;
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition
	(
		GetWarriorHeroControllerFromActorInfo(),
		ActorToLockOn->GetActorLocation(),
		ScreenPosition,
		true
	);
	if(TargetLockWidgetSize == FVector2D::ZeroVector)
	{
		DrawnWidget->WidgetTree->ForEachWidget
		(
			[this](UWidget* FoundWidget)
			{
				if (USizeBox* SizeBox = Cast<USizeBox>(FoundWidget))
				{
					TargetLockWidgetSize.X = SizeBox->GetWidthOverride();
					TargetLockWidgetSize.Y = SizeBox->GetHeightOverride();
				}
			}
		);
	}
	ScreenPosition -= (TargetLockWidgetSize / 2.f);
	DrawnWidget->SetPositionInViewport(ScreenPosition, false);
}

void UHeroGameplayAbility_ToggleTarget::SetLockTargetMovementSpeed()
{
	CachedMovementSpeed = GetMyWarriorHeroCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed;
	GetMyWarriorHeroCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = SetTargetLockMovementSpeed;
}

void UHeroGameplayAbility_ToggleTarget::ResetLockTargetMovementSpeed()
{
	if(CachedMovementSpeed > 0.f)
	{
		GetMyWarriorHeroCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = CachedMovementSpeed;
	}
}
