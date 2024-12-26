
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PerceptionSubsystem.generated.h"

class UPerceptionComponent;
class USense;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActorDetectedSystemEvent, AActor*, Actor, TSubclassOf<USense>, Sense);

UCLASS()
class EJERCICIO2CPP_API UPerceptionSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	friend UPerceptionComponent;

public:

	FOnActorDetectedSystemEvent OnActorDetectedSystemEvent;

	FORCEINLINE UPerceptionSubsystem* GetPerceptionSubsystem() { return this; };
	
	void RegisterActorWithPerception(AActor* Actor);
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "PerceptionSystem")
	void InitPerceptionInfo(AActor* Actor, const TArray<TSubclassOf<USense>>& Sense);

	UFUNCTION(BlueprintCallable, Category = "PerceptionSystem")
	void RemoveSenseFromActor(AActor* InActor, const TSubclassOf<USense>& Sense);

	UFUNCTION(BlueprintCallable, Category = "PerceptionSystem")
	void AddSenseToActor(AActor* InActor, const TSubclassOf<USense>& InSense);

	UFUNCTION(BlueprintCallable, Category = "PerceptionSystem")
	void ActivatePerceptionFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "PerceptionSystem")
	void ActivatePerceptionFromActors(TArray<AActor*> InActors);

	UFUNCTION(BlueprintCallable, Category = "PerceptionSystem")
	void DeactivatePerceptionFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "PerceptionSystem")
	void DeactivatePerceptionFromActors(TArray<AActor*> InActors);

	void RegisterActorsWithPerception();

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<AActor*> PerceptionSubsystemActors;

	UPROPERTY(EditDefaultsOnly)
	TArray<AActor*> DetectedActors;

	UFUNCTION()
	void OnActorDetected( AActor* Actor, TSubclassOf<USense> Sense);
	
};
