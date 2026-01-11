// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbilitySystem/Utils/Fireball.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AbilitySystemGlobals.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"

// Sets default values
AFireball::AFireball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);
	Collision->InitSphereRadius(15.0f);
	Collision->SetCollisionProfileName(TEXT("Projectile"));
	Collision->OnComponentHit.AddDynamic(this, &AFireball::OnHit);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 2000.f;
	ProjectileMovement->MaxSpeed = 2000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.f;

	InitialLifeSpan = 5.0f;
}

// Called when the game starts or when spawned
void AFireball::BeginPlay()
{
	Super::BeginPlay();
}

void AFireball::OnHit(
	UPrimitiveComponent* HitComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, 
	const FHitResult& Hit)
{
	if (!OtherActor || OtherActor == this) return;

	if (OtherActor == GetOwner() || OtherActor == GetInstigator()) return;

	UAbilitySystemComponent* TargetASC =
		UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OtherActor);
	if (!TargetASC)
	{
		Destroy();
		return;
	}

	AActor* SourceActor = GetOwner();
	UAbilitySystemComponent* SourceASC =
		SourceActor ? UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(SourceActor) : nullptr;
	if (!SourceASC)
	{
		Destroy();
		return;
	}

	static const FGameplayTag TAG_State_Burn =
		FGameplayTag::RequestGameplayTag(TEXT("State.Burn"));

	static const FGameplayTag TAG_Data_Damage =
		FGameplayTag::RequestGameplayTag(TEXT("Data.Damage"));

	const bool bIsBurning = TargetASC->HasMatchingGameplayTag(TAG_State_Burn);
	const float Damage = bIsBurning ? 20.f : 10.f;
	UE_LOG(LogTemp, Log, TEXT("bIsBurning = %d"), bIsBurning);
	FGameplayEffectContextHandle ContextHandle = SourceASC->MakeEffectContext();
	ContextHandle.AddHitResult(Hit);

	if (GE_Fireball_Damage)
	{
		FGameplayEffectSpecHandle DamageSpec = SourceASC->MakeOutgoingSpec(GE_Fireball_Damage, 1.f, ContextHandle);
		if (DamageSpec.IsValid())
		{
			DamageSpec.Data->SetSetByCallerMagnitude(TAG_Data_Damage, -Damage);

			SourceASC->ApplyGameplayEffectSpecToTarget(*DamageSpec.Data.Get(), TargetASC);
		}
	}

	if (GE_Burn)
	{
		FGameplayEffectSpecHandle BurnSpec = SourceASC->MakeOutgoingSpec(GE_Burn, 1.f, ContextHandle);
		if (BurnSpec.IsValid())
		{
			SourceASC->ApplyGameplayEffectSpecToTarget(*BurnSpec.Data.Get(), TargetASC);
		}
	}

	Destroy();
}

