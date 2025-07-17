// Aditya Singh Gajawat All Rights Reserved

#include "Blueprint Function Library/CharacterBluprintFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Ability System/WarriorAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameplayTag/MyGameplayTags.h"

#include "WarriorDebugHelper.h"

UWarriorAbilitySystemComponent* UCharacterBluprintFunctionLibrary::NativeGetWarriorASCFromActor(AActor* InActor)
{
    check(InActor);

    return CastChecked<UWarriorAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UCharacterBluprintFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
    UWarriorAbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);

    if (!ASC->HasMatchingGameplayTag(TagToAdd))
    {
        ASC->AddLooseGameplayTag(TagToAdd);
    }
}

bool UCharacterBluprintFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
    UWarriorAbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);
    return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UCharacterBluprintFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EWarriorConfirmType& OutConfirmType)
{
    OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EWarriorConfirmType::Yes : EWarriorConfirmType::No;
}

void UCharacterBluprintFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
    UWarriorAbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);

    if (ASC->HasMatchingGameplayTag(TagToRemove))
    {
        ASC->RemoveLooseGameplayTag(TagToRemove);
    }
}

UPawnCombatComponent* UCharacterBluprintFunctionLibrary::NativeGetCombatComponentFromActor(AActor* InActor)
{
    if(IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
    {
        return PawnCombatInterface->Interface_ReturnPawnCombatComponent();
    }
    return nullptr;
}

UPawnCombatComponent* UCharacterBluprintFunctionLibrary::BP_GetCombatComponentFromActor(AActor* InActor, EValid& OutValidCheck)
{
    UPawnCombatComponent* PawnCombatComponent =  NativeGetCombatComponentFromActor(InActor);
    OutValidCheck = PawnCombatComponent ? EValid::Valid : EValid::InValid;
    return PawnCombatComponent;
}

bool UCharacterBluprintFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
    check(QueryPawn && TargetPawn);
    IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
    IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());
    if(QueryTeamAgent && TargetTeamAgent)
    {   
        return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
    }
    return false;
}

FGameplayTag UCharacterBluprintFunctionLibrary::ComputeHitReactDirectionForATag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference)
{
    check(InAttacker && InVictim);

    // Get the direction the victim is facing (forward vector)
    FVector VictimForwardVector = InVictim->GetActorForwardVector();
   
    // Calculate the direction from the victim to the attacker (vector pointing from victim to attacker)
    // Subtracting gives a vector from victim to attacker, then GetSafeNormal makes it a unit direction vector
    FVector VectorFromVictimToAttackerNormalized = (InVictim->GetActorLocation() - InAttacker->GetActorLocation()).GetSafeNormal();
    
    // Use the dot product to measure how aligned the two direction vectors are (Victim's forward vs. direction to attacker)
    // DotProduct returns a value between -1 (opposite) to 1 (same direction)
    const float DotResult = FVector::DotProduct(VictimForwardVector, VectorFromVictimToAttackerNormalized);
   
    // Convert the dot product result to an angle in degrees
    // This gives the actual angle between the forward direction and the direction to the attacker
    OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);
    
    // Use the cross product to determine the side (left or right) the attacker is on, relative to the victim's forward direction
    // The sign of the Z component tells us the side: 
    // - If CrossResult.Z > 0 → attacker is on the right, right → angle should be positive
    // - If CrossResult.Z < 0 → attacker is on the left, left → angle should be negative
    const FVector CrossResult = FVector::CrossProduct(VictimForwardVector, VectorFromVictimToAttackerNormalized);
   
    if (CrossResult.Z < 0.f) { OutAngleDifference *= -1.f; }
   
    if (OutAngleDifference >= -45.f && OutAngleDifference <= 45.f)
    {
        return WarriorGameplayTags::Shared_Status_HitReact_Front;
    }
    else if (OutAngleDifference < -45.f && OutAngleDifference >= -135.f)
    {
        return WarriorGameplayTags::Shared_Status_HitReact_Left;
    }
    else if (OutAngleDifference < -135.f || OutAngleDifference>135.f)
    {
        return WarriorGameplayTags::Shared_Status_HitReact_Back;
    }
    else if (OutAngleDifference > 45.f && OutAngleDifference <= 135.f)
    {
        return WarriorGameplayTags::Shared_Status_HitReact_Right;
    }

    return WarriorGameplayTags::Shared_Status_HitReact_Front;
}

bool UCharacterBluprintFunctionLibrary::CheckForValidBlock(AActor* InDefender, AActor* InAttacker)
{
    const float DotProductForwardVectorOfActors = FVector::DotProduct(InDefender->GetActorForwardVector(), InAttacker->GetActorForwardVector());
   
    const FString DebugString = FString::Printf(TEXT("Dot Results: %f %s"), DotProductForwardVectorOfActors, DotProductForwardVectorOfActors < 0.f ? TEXT("Is Valid Block") : TEXT("Invalid Block"));
    Debug::Print(DebugString, DotProductForwardVectorOfActors < 0.f ? FColor::Green : FColor::Red);
    
    return DotProductForwardVectorOfActors<0.f;
}

