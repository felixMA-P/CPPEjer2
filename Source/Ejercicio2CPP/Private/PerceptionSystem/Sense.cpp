

#include "Ejercicio2CPP/Public/PerceptionSystem/Sense.h"
#include "Ejercicio2CPP/Public/PerceptionSystem/PerceptionComponent.h"

void USense::DetectStimulus(const TArray<AActor*>& InActors, UPerceptionComponent* ParentPerceptionComponent)
{
	if (!ParentPerceptionComponent)
	{
		UE_LOG(LogTemp, Log, TEXT("The perception component of this sense is missing: '%s'."), *GetClass()->GetClassPathName().ToString());
		return;
	}
	
	TArray<AActor*> DetectedActors = InActors.FilterByPredicate([](AActor* Actor)
	{
		return Actor->FindComponentByClass<UPerceptionComponent>();
	});
	
	ParentPerceptionComponent->SenseStimulusDetected(GetClass(), DetectedActors);
}

void USense::PerformSense(UPerceptionComponent* ParentPerceptionComponent)
{
	PerformSense_Event(ParentPerceptionComponent);
}

