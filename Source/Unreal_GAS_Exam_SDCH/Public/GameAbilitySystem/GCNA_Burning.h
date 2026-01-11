// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "GCNA_Burning.generated.h"

/**
 * 
 */

class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class UNREAL_GAS_EXAM_SDCH_API AGCNA_Burning : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()
	
public:
	AGCNA_Burning();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	TObjectPtr<UNiagaraSystem> BurningParticle;

	UPROPERTY()
	TObjectPtr<UNiagaraComponent> SpawnedComp;

	virtual bool OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	virtual bool OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;

private:
	void SpawnAndAttach(AActor* MyTarget, const FGameplayCueParameters& Parameters);
};
