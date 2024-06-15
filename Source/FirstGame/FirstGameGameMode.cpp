// Copyright Epic Games, Inc. All Rights Reserved.

#include "FirstGameGameMode.h"
#include "UObject/ConstructorHelpers.h"

AFirstGameGameMode::AFirstGameGameMode() : Super() {
	
	static ConstructorHelpers::FClassFinder<APawn> playerClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_PlayerCharacter"));
	if (!playerClassFinder.Succeeded()) return;
	
	DefaultPawnClass = playerClassFinder.Class;

}