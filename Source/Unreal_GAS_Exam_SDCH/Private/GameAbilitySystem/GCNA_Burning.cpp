// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbilitySystem/GCNA_Burning.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/SkeletalMeshComponent.h"

AGCNA_Burning::AGCNA_Burning()
{
	bAutoDestroyOnRemove = true;
}

bool AGCNA_Burning::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	SpawnAndAttach(MyTarget, Parameters);
	return true;
}

bool AGCNA_Burning::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	UE_LOG(LogTemp, Warning, TEXT("[BurnCue] OnRemove called. Target=%s"), *GetNameSafe(MyTarget));

	if (SpawnedComp)
	{
		SpawnedComp->DestroyComponent();
		SpawnedComp = nullptr;
	}
	return true;
}

void AGCNA_Burning::SpawnAndAttach(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	if (!MyTarget || !BurningParticle || SpawnedComp) return;

	USkeletalMeshComponent* Skel = MyTarget->FindComponentByClass<USkeletalMeshComponent>();

	FName BoneName = NAME_None;
	if (Parameters.EffectContext.IsValid())
	{
		if (const FHitResult* HR = Parameters.EffectContext.GetHitResult())
		{
			BoneName = HR->BoneName;
		}
	}

	const FVector SpawnLoc = Parameters.Location; // ImpactPoint
	const FRotator SpawnRot = Parameters.Normal.Rotation();

	if (Skel && BoneName != NAME_None)
	{
		SpawnedComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
			BurningParticle,
			Skel,
			BoneName,
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			EAttachLocation::SnapToTarget,
			false
		);
	}
	else if (Skel)
	{
		SpawnedComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
			BurningParticle,
			Skel,
			NAME_None,
			Skel->GetComponentTransform().InverseTransformPosition(SpawnLoc),
			SpawnRot,
			EAttachLocation::KeepRelativeOffset,
			false
		);
	}
	else
	{
		SpawnedComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(), BurningParticle, SpawnLoc, SpawnRot
		);
	}
}
