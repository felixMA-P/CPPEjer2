// Copyright Epic Games, Inc. All Rights Reserved.

#include "Ejercicio2CPPGameMode.h"
#include "Ejercicio2CPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEjercicio2CPPGameMode::AEjercicio2CPPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
