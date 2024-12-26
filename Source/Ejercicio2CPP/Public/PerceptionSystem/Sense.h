
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Sense.generated.h"

class UPerceptionComponent;

UCLASS(Blueprintable, BlueprintType)
class EJERCICIO2CPP_API USense : public UObject
{
	GENERATED_BODY()
	
protected:
	
	UFUNCTION(BlueprintImplementableEvent)
	void PerformSense_Event(UPerceptionComponent* ParentPerceptionComponent);

	UFUNCTION(BlueprintCallable)
	void DetectStimulus(const  TArray<AActor*>& InHitResults, UPerceptionComponent* ParentPerceptionComponent);
	
public:
	
	void PerformSense(UPerceptionComponent* ParentPerceptionComponent);
	
};
