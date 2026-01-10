// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameAbilitySystem/ResourceAttributeSet.h"
#include "GameAbilitySystem/Utils/AbilityEnums.h"
#include "Components/WidgetComponent.h"
#include "EnhancedInputComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	ResourceAttributeSet = CreateDefaultSubobject<UResourceAttributeSet>(TEXT("ResourceAttributeSet"));
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInput)
	{
		EnhancedInput->BindAction(IA_Fireball, ETriggerEvent::Started, this, &APlayerCharacter::SpellFireball);
	}
}

void APlayerCharacter::TestManaChange(float Amount)
{
	ResourceAttributeSet->SetMana(Amount);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		if (FireballClass)
		{
			AbilitySystemComponent->GiveAbility(
				FGameplayAbilitySpec
				(
					FireballClass,
					1,
					static_cast<int32>(EAbilityInputID::Fireball),
					this
				)
			);
		}
	}

	BindGASDelegates();
	PushManaOnce();
}

void APlayerCharacter::BindGASDelegates()
{
	if (!AbilitySystemComponent || !ResourceAttributeSet) return;

	AbilitySystemComponent
		->GetGameplayAttributeValueChangeDelegate(ResourceAttributeSet->GetManaAttribute())
		.AddUObject(this, &APlayerCharacter::OnManaAttrChanged);

	AbilitySystemComponent
		->GetGameplayAttributeValueChangeDelegate(ResourceAttributeSet->GetMaxManaAttribute())
		.AddUObject(this, &APlayerCharacter::OnMaxManaAttrChanged);
}

void APlayerCharacter::PushManaOnce()
{
	if (!ResourceAttributeSet) return;

	OnManaChanged.Broadcast(ResourceAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(ResourceAttributeSet->GetMaxMana());
}

void APlayerCharacter::OnManaAttrChanged(const FOnAttributeChangeData& Data)
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void APlayerCharacter::OnMaxManaAttrChanged(const FOnAttributeChangeData& Data)
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}

void APlayerCharacter::SpellFireball()
{
	UE_LOG(LogTemp, Log, TEXT("Try Spell Fireball"));
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(EAbilityInputID::Fireball));
	}
}
