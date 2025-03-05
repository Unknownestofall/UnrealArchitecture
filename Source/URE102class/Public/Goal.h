// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "Goal.generated.h"

UCLASS()
class URE102CLASS_API AGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoal();
	
	UPROPERTY(EditAnywhere, Category = "FX")
	UNiagaraSystem* CelebrationEffect;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp,AActor* Other,class UPrimitiveComponent* OtherComp,
		bool bSelfMoved,FVector HitLocation,FVector HitNormal,FVector NormalImpulse,const FHitResult& Hit) override;

	void HandleGoalReached();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool HasBeenHit = false;
	bool bWaitingForParticleFX = false;

	UPROPERTY() UNiagaraComponent* CelebrationEffectComponent;
};
