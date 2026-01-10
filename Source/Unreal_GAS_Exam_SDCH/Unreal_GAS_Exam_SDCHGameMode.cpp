// Copyright Epic Games, Inc. All Rights Reserved.

#include "Unreal_GAS_Exam_SDCHGameMode.h"
#include "Unreal_GAS_Exam_SDCHCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnreal_GAS_Exam_SDCHGameMode::AUnreal_GAS_Exam_SDCHGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
