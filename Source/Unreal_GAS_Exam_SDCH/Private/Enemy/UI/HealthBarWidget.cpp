// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/UI/HealthBarWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UHealthBarWidget::UpdateCurrentHealth_Implementation(float InValue)
{
	Current->SetText(FText::AsNumber(FMath::RoundToInt(InValue)));
	CurrentValue = InValue;
	HealthProgress->SetPercent(CurrentValue / MaxValue);
}

void UHealthBarWidget::UpdateMaxHealth_Implementation(float InValue)
{
	Max->SetText(FText::AsNumber(FMath::RoundToInt(InValue)));
	MaxValue = InValue;
	HealthProgress->SetPercent(CurrentValue / MaxValue);
}
