
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SenseBlueprintFunctionLibrary.generated.h"

UCLASS()
class EJERCICIO2CPP_API USenseBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetActorsInRadius"))
	static TArray<AActor*> GetActorsInRadius(	const UObject* WorldContextObject,
												const FVector SpherePos, float SphereRadius,
												const TArray<TEnumAsByte<EObjectTypeQuery> > & ObjectTypes,
												UClass* ActorClassFilter, const TArray<AActor*>& ActorsToIgnore);


	
};
