// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HaveHealth.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHaveHealth : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREAL_GAS_EXAM_SDCH_API IHaveHealth
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resource")
	void UpdateCurrentHealth(float InValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resource")
	void UpdateMaxHealth(float InValue);
};
