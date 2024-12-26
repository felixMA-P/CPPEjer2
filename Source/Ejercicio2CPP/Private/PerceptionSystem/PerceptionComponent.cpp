
#include "Ejercicio2CPP/Public/PerceptionSystem/PerceptionComponent.h"

#include "PerceptionSystem/Sense.h"


UPerceptionComponent::UPerceptionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


void UPerceptionComponent::BeginPlay()
{
	Super::BeginPlay();

	AttachToParentSkeletalMesh();

	GetWorld()->GetTimerManager().SetTimer(
	   SensesTimerHandle,
	   this,
	   &UPerceptionComponent::TickSenses,
	   IntervalChecker,
	   true
   );
}

//This function creates the inital map of senses, and its only called by the subsystem
//Sets the values of the map to true by default
void UPerceptionComponent::InitSenses(TArray<TSubclassOf<USense>>& InSenses)
{
	for (const TSubclassOf<USense>& Sense : InSenses)
	{
		Senses.Add(Sense);
		Senses[Sense] = true; 
	}
}

void UPerceptionComponent::AddSense(const TSubclassOf<USense>& Sense)
{
	Senses.FindOrAdd(Sense);
}

void UPerceptionComponent::RemoveSense(const TSubclassOf<USense>& Sense)
{
	if (Senses.Contains(Sense))
	{
		Senses.Remove(Sense);
	}
}

void UPerceptionComponent::ActivateSense(const TSubclassOf<USense>& Sense)
{
	if (Senses.Contains(Sense))
	{
		Senses[Sense] = true;
	}
}

void UPerceptionComponent::DeactivateSense(const TSubclassOf<USense>& Sense)
{
	if (Senses.Contains(Sense))
	{
		Senses[Sense] = false;
	}
}

void UPerceptionComponent::TogglePerception(bool bAction)
{
	if (bAction)
	{
		GetWorld()->GetTimerManager().UnPauseTimer(SensesTimerHandle);
		bActivate = true;
	}
	else
	{
		GetWorld()->GetTimerManager().PauseTimer(SensesTimerHandle);
		bActivate = false;
	}
	
}

void UPerceptionComponent::TickSenses()
{
	for (const TTuple<TSubclassOf<USense>, bool> & Sense : Senses)
	{
		if (Sense.Value) Sense.Key.GetDefaultObject()->PerformSense(this);
	}
}

void UPerceptionComponent::AttachToParentSkeletalMesh()
{
	if (USkeletalMeshComponent* SkmComp = GetOwner()->GetComponentByClass<USkeletalMeshComponent>())
	{
		if (SkmComp->DoesSocketExist(TargetSocketName))
		{
			AttachToComponent(SkmComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TargetSocketName);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AutoSocketAttachComponent: the socket '%s' doesnt exists."), *TargetSocketName.ToString());
		}
	}
}


void UPerceptionComponent::SenseStimulusDetected(const TSubclassOf<USense>& Sense, TArray<AActor*> ActorsDetected)
{
	for (AActor* ActorDetected : ActorsDetected)
	{
		DetectedActors.AddUnique(ActorDetected);
		OnActorDetected.Broadcast(ActorDetected, Sense);
	}
}

void UPerceptionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

