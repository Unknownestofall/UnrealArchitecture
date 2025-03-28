// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class URE102CLASS_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere) FVector LocalStartPos;
	UPROPERTY(EditAnywhere) FVector LocalEndPos;
	UPROPERTY(EditAnywhere) float MovementSpeed;

private:
	FVector WorldStartPos;
	FVector WorldEndPos;
	bool bMovingToEnd;
		
};
