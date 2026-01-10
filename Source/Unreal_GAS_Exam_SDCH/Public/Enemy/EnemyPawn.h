// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "EnemyPawn.generated.h"

UCLASS()
class UNREAL_GAS_EXAM_SDCH_API AEnemyPawn : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyPawn();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const {
		return AbilitySystemComponent;
	};

	UFUNCTION(BlueprintCallable)
	void TestHealth(float InValue);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void InitHealth();
	void OnHealthChange(const FOnAttributeChangeData& InData);
	void OnMaxHealthChange(const FOnAttributeChangeData& InData);

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<class USkeletalMeshComponent> SkeletalMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<class UWidgetComponent> BarWigetComponent = nullptr;

private:
	UPROPERTY()
	TObjectPtr<class UResourceAttributeSet> ResourceAttributeSet = nullptr;
};
