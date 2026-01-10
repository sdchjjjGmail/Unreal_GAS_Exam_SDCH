// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbilitySystem/GA_Fireball.h"
#include "GameAbilitySystem/Utils/Fireball.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"

UGA_Fireball::UGA_Fireball()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_Fireball::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	if (!Character || !ProjectileClass)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	const FVector Location =
		Character->GetMesh()
		? Character->GetMesh()->GetSocketLocation(TEXT("Head"))
		: Character->GetActorLocation() + Character->GetActorForwardVector() * 100.f;

	const FRotator SpawnRotation = Character->GetControlRotation();

	FActorSpawnParameters Params;
	Params.Owner = Character;
	Params.Instigator = Character;

	AFireball* SpawnedFireball = Character->GetWorld()->SpawnActor<AFireball>(
		ProjectileClass,
		Location,
		SpawnRotation,
		Params
	);

	if (SpawnedFireball)
	{
		SpawnedFireball->SetOwner(Character);
		SpawnedFireball->SetInstigator(Character);

		if (USphereComponent* Col = SpawnedFireball->GetCollisionComponent())
		{
			Col->IgnoreActorWhenMoving(Character, true);
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
