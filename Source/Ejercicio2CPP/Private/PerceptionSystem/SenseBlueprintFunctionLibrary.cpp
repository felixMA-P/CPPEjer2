

#include "PerceptionSystem/SenseBlueprintFunctionLibrary.h"

#include "Kismet/KismetSystemLibrary.h"

TArray<AActor*> USenseBlueprintFunctionLibrary::GetActorsInRadius(const UObject* WorldContextObject,
	const FVector SpherePos, const float SphereRadius, const TArray<TEnumAsByte<EObjectTypeQuery> > & ObjectTypes,
	UClass* ActorClassFilter, const TArray<AActor*>& ActorsToIgnore)
{

	check(WorldContextObject);
	
	TArray<AActor*> Result;

	UKismetSystemLibrary::SphereOverlapActors(WorldContextObject,
												SpherePos,
												SphereRadius,
												ObjectTypes,
												ActorClassFilter,
												ActorsToIgnore,
												Result);
	
	
	return Result;
}
