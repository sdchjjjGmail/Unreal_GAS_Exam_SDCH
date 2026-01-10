// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/HaveHealth.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */

class UProgressBar;
class UTextBlock;

UCLASS()
class UNREAL_GAS_EXAM_SDCH_API UHealthBarWidget : public UUserWidget, public IHaveHealth
{
	GENERATED_BODY()
	
public:
	virtual void UpdateCurrentHealth_Implementation(float InValue) override;
	virtual void UpdateMaxHealth_Implementation(float InValue) override;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthProgress = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Current = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Max = nullptr;

private:
	float CurrentValue = 0.0f;
	float MaxValue = 1.0f;
};
