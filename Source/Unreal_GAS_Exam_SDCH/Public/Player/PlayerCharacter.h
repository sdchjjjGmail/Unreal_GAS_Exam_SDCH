// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaValueChanged, float, NewValue);

class UResourceAttributeSet;
class UWidgetComponent;

UCLASS()
class UNREAL_GAS_EXAM_SDCH_API APlayerCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {
		return AbilitySystemComponent;
	};

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void TestManaChange(float Amount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void BindGASDelegates();
	void PushManaOnce();

	void OnManaAttrChanged(const FOnAttributeChangeData& Data);
	void OnMaxManaAttrChanged(const FOnAttributeChangeData& Data);

public:
	UPROPERTY(BlueprintAssignable, Category = "UI|Mana")
	FOnManaValueChanged OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "UI|Mana")
	FOnManaValueChanged OnMaxManaChanged;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

private:
	UPROPERTY()
	TObjectPtr<UResourceAttributeSet> ResourceAttributeSet = nullptr;
};
