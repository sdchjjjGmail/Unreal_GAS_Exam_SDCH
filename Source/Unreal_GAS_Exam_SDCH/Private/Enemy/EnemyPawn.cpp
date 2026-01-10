// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyPawn.h"
#include "AbilitySystemComponent.h"
#include "GameAbilitySystem/ResourceAttributeSet.h"

// Sets default values
AEnemyPawn::AEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	ResourceAttributeSet = CreateDefaultSubobject<UResourceAttributeSet>(TEXT("ResourceAttributeSet"));
}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		FOnGameplayAttributeValueChange& onHealthChange =
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UResourceAttributeSet::GetHealthAttribute());
		onHealthChange.AddUObject(this, &AEnemyPawn::OnHealthChange);

		FOnGameplayAttributeValueChange& onMaxHealthChange =
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UResourceAttributeSet::GetMaxHealthAttribute());
		onMaxHealthChange.AddUObject(this, &AEnemyPawn::OnMaxHealthChange);
	}
}

void AEnemyPawn::OnHealthChange(const FOnAttributeChangeData& InData)
{

}

void AEnemyPawn::OnMaxHealthChange(const FOnAttributeChangeData& InData)
{

}

// Called to bind functionality to input
void AEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

