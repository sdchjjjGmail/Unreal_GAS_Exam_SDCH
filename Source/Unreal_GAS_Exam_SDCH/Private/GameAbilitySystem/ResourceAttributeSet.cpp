// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbilitySystem/ResourceAttributeSet.h"
#include "GameplayEffectExtension.h"

UResourceAttributeSet::UResourceAttributeSet()
{
	InitMaxMana(100.0f);
	InitMana(100.0f);
}

void UResourceAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UResourceAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
	}
}
