// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE4_ProjectGameModeBase.h"
#include "GameFramework/Character.h"

AUE4_ProjectGameModeBase::AUE4_ProjectGameModeBase()
{
	static ConstructorHelpers::FClassFinder<ACharacter> myCharacter(TEXT("Blueprint'/Game/BluePrint/BP_MyCharacter.BP_MyCharacter_C'"));

	if (myCharacter.Succeeded())
	{
		DefaultPawnClass = myCharacter.Class;
	}
}