// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyPawn.h"
#include "Components/WidgetComponent.h"
#include "AbilitySystemComponent.h"
#include "GameAbilitySystem/ResourceAttributeSet.h"
#include "Interface/HaveHealth.h"

// Sets default values
AEnemyPawn::AEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal"));
	SkeletalMesh->SetupAttachment(RootComponent);

	BarWigetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	BarWigetComponent->SetupAttachment(SkeletalMesh);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	ResourceAttributeSet = CreateDefaultSubobject<UResourceAttributeSet>(TEXT("ResourceAttributeSet"));
}

void AEnemyPawn::TestHealth(float InValue)
{
	ResourceAttributeSet->SetHealth(InValue);
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

		InitHealth();
	}
}

void AEnemyPawn::InitHealth()
{
	if (ResourceAttributeSet)
	{
		IHaveHealth::Execute_UpdateMaxHealth(BarWigetComponent->GetWidget(), ResourceAttributeSet->GetMaxHealth());
		IHaveHealth::Execute_UpdateCurrentHealth(BarWigetComponent->GetWidget(), ResourceAttributeSet->GetHealth());
	}
}

void AEnemyPawn::OnHealthChange(const FOnAttributeChangeData& InData)
{
	if (ResourceAttributeSet)
	{
		IHaveHealth::Execute_UpdateCurrentHealth(BarWigetComponent->GetWidget(), ResourceAttributeSet->GetHealth());
	}
}

void AEnemyPawn::OnMaxHealthChange(const FOnAttributeChangeData& InData)
{
	if (ResourceAttributeSet)
	{
		IHaveHealth::Execute_UpdateMaxHealth(BarWigetComponent->GetWidget(), ResourceAttributeSet->GetMaxHealth());
	}
}

// Called to bind functionality to input
void AEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

