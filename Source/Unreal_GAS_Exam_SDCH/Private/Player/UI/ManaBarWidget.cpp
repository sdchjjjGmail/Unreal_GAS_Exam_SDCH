// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UI/ManaBarWidget.h"
#include "Player/PlayerCharacter.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UManaBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (APawn* Pawn = GetOwningPlayerPawn())
	{
		CachedPlayer = Cast<APlayerCharacter>(Pawn);
	}

	if (CachedPlayer)
	{
		CachedPlayer->OnManaChanged.AddDynamic(this, &UManaBarWidget::HandleMana);
		CachedPlayer->OnMaxManaChanged.AddDynamic(this, &UManaBarWidget::HandleMaxMana);
	}
}

void UManaBarWidget::NativeDestruct()
{
	if (CachedPlayer)
	{
		CachedPlayer->OnManaChanged.RemoveDynamic(this, &UManaBarWidget::HandleMana);
		CachedPlayer->OnMaxManaChanged.RemoveDynamic(this, &UManaBarWidget::HandleMaxMana);
	}
	CachedPlayer = nullptr;

	Super::NativeDestruct();
}

void UManaBarWidget::HandleMana(float NewMana)
{
	CurrentValue = NewMana;
	RefreshManaUI();
}

void UManaBarWidget::HandleMaxMana(float NewMaxMana)
{
	MaxValue = FMath::Max(NewMaxMana, 0.0f);
	RefreshManaUI();
}

void UManaBarWidget::RefreshManaUI()
{
	if (ManaProgress)
	{
		ManaProgress->SetPercent(CurrentValue / MaxValue);
	}
	if (Current)
	{
		Current->SetText(FText::AsNumber(FMath::RoundToInt(CurrentValue)));
	}
	if (Max)
	{
		Max->SetText(FText::AsNumber(FMath::RoundToInt(MaxValue)));
	}
}
