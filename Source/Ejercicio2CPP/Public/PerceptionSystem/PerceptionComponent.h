
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PerceptionComponent.generated.h"

class UPerceptionSubsystem;
class USense;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActorDetectedEvent, AActor*, Actor, TSubclassOf<USense>, Sense);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EJERCICIO2CPP_API UPerceptionComponent : public USceneComponent
{
	GENERATED_BODY()

	friend UPerceptionSubsystem;
	friend USense;

public:
	UPerceptionComponent();

protected:
	virtual void BeginPlay() override;

	void AddSense(const TSubclassOf<USense>& Sense);

	void RemoveSense(const TSubclassOf<USense>& Sense);

	void ActivateSense(const TSubclassOf<USense>& Sense);

	void DeactivateSense(const TSubclassOf<USense>& Sense);

	void TogglePerception(bool bAction);

	UPROPERTY(EditDefaultsOnly,  Category = "PerceptionSettings")
	float IntervalChecker = 2.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "PerceptionSettings")
	FName TargetSocketName = "Head";

	void SenseStimulusDetected(const TSubclassOf<USense>& Sense, TArray<AActor*> ActorsDetected);

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:

	void InitSenses(TArray<TSubclassOf<USense>>& Senses);

	void TickSenses();

	void AttachToParentSkeletalMesh();
	
	UPROPERTY(EditDefaultsOnly)
	TMap<TSubclassOf<USense>, bool> Senses;

	FTimerHandle SensesTimerHandle;

	UPROPERTY(EditDefaultsOnly)
	bool bActivate = true;

	UPROPERTY(EditDefaultsOnly)
	TArray<AActor*> DetectedActors;

	UPROPERTY(BlueprintAssignable, Category = "ActionSystem")
	FOnActorDetectedEvent OnActorDetected;
	
};
