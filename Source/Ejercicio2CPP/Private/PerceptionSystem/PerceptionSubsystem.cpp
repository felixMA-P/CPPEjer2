

#include "Ejercicio2CPP/Public/PerceptionSystem/PerceptionSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "LevelInstance/LevelInstanceTypes.h"
#include "PerceptionSystem/PerceptionComponent.h"


void UPerceptionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	RegisterActorsWithPerception();
	
	GetWorld()->AddOnActorSpawnedHandler(FOnActorSpawned::FDelegate::CreateUObject(this, &UPerceptionSubsystem::RegisterActorWithPerception));
}

void UPerceptionSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UPerceptionSubsystem::InitPerceptionInfo(AActor* Actor, const TArray<TSubclassOf<USense>>& Sense)
{
	if (Actor && PerceptionSubsystemActors.Contains(Actor))
	{
		UPerceptionComponent* PerComp = Actor->GetComponentByClass<UPerceptionComponent>();

		for (const TSubclassOf<USense>& Sense : Sense)
		{
			Actor->GetComponentByClass<UPerceptionComponent>()->AddSense(Sense);
		}
	}
}

void UPerceptionSubsystem::RemoveSenseFromActor(AActor* InActor, const TSubclassOf<USense>& InSense)
{
	if (InActor && PerceptionSubsystemActors.Contains(InActor))
	{
		InActor->GetComponentByClass<UPerceptionComponent>()->RemoveSense(InSense);
	}
}

void UPerceptionSubsystem::AddSenseToActor(AActor* InActor, const TSubclassOf<USense>& InSense)
{
	if (InActor && PerceptionSubsystemActors.Contains(InActor))
	{
		InActor->GetComponentByClass<UPerceptionComponent>()->AddSense(InSense);
	}
}


void UPerceptionSubsystem::ActivatePerceptionFromActor(AActor* InActor)
{
	if (PerceptionSubsystemActors.Contains(InActor))
	{
		InActor->GetComponentByClass<UPerceptionComponent>()->TogglePerception(true);
	}
}

void UPerceptionSubsystem::ActivatePerceptionFromActors(TArray<AActor*> InActors)
{
	for (AActor* Actor : InActors)
	{
		ActivatePerceptionFromActor(Actor);
	}
}

void UPerceptionSubsystem::DeactivatePerceptionFromActor(AActor* InActor)
{
	if (PerceptionSubsystemActors.Contains(InActor))
	{
		InActor->GetComponentByClass<UPerceptionComponent>()->TogglePerception(false);
	}
}

void UPerceptionSubsystem::DeactivatePerceptionFromActors(TArray<AActor*> InActors)
{
	for (AActor* Actor : InActors)
	{
		DeactivatePerceptionFromActor(Actor);
	}
}

void UPerceptionSubsystem::RegisterActorsWithPerception()
{

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, AActor::StaticClass(), OutActors);
	
	PerceptionSubsystemActors = OutActors.FilterByPredicate([](AActor* Actor)
	{
		return Actor->FindComponentByClass<UPerceptionComponent>();
	});

	//Delegate bind
	for (auto OutActor : PerceptionSubsystemActors)
	{
		OutActor->FindComponentByClass<UPerceptionComponent>()->OnActorDetected.AddDynamic(this, &UPerceptionSubsystem::OnActorDetected);
	}
	
}

void UPerceptionSubsystem::OnActorDetected(AActor* Actor, TSubclassOf<USense> Sense)
{
	OnActorDetectedSystemEvent.Broadcast(Actor, Sense);
}


void UPerceptionSubsystem::RegisterActorWithPerception(AActor* Actor)
{
	UPerceptionComponent* Comp = Actor->FindComponentByClass<UPerceptionComponent>();
	
	if(Actor && Comp)
	{
		PerceptionSubsystemActors.AddUnique(Actor);
		Comp->OnActorDetected.AddDynamic(this, &UPerceptionSubsystem::OnActorDetected);
	}
	
}
