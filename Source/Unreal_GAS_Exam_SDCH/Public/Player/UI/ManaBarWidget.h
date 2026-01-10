// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ManaBarWidget.generated.h"

/**
 * 
 */

class UProgressBar;
class UTextBlock;

UCLASS()
class UNREAL_GAS_EXAM_SDCH_API UManaBarWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void HandleMana(float NewMana);

	UFUNCTION()
	void HandleMaxMana(float NewMaxMana);

private:
	void RefreshManaUI();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ManaProgress = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Current = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Max = nullptr;

private:
	UPROPERTY() 
	TObjectPtr<class APlayerCharacter> CachedPlayer = nullptr;

	float CurrentValue = 0.0f;
	float MaxValue = 1.0f;
};
