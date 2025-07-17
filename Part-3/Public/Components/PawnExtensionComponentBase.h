// Aditya Singh Gajawat All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnExtensionComponentBase.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAS_RPG_API UPawnExtensionComponentBase : public UActorComponent
{
	GENERATED_BODY()
protected:
	//We can use GetOwningPawn() if we want to cast to our hero character or enemy character this is the version we can use.
	template<class T>
	T* GetOwningPawn() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, "'T' Template Parameter to get GetPawn must be derived from APawn");
		return CastChecked<T>(GetOwner());
	}

	//We don't cast to specific type and get hold of owning pawn, use this version.
	APawn* GetOwningPawn() const {
		return GetOwningPawn<APawn>();
	}

	template <class T>
	T* GetOwningController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value, "'T' Template Parameter to get GetController must be derived from AController");
		return GetOwningPawn<APawn>()->GetController<T>();
	}
};
