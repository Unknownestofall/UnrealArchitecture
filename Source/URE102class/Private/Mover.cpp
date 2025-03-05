// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MovementSpeed = 100.f;
	bMovingToEnd = true;
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner()){
		USceneComponent* ActorRoot = Owner->GetRootComponent();
		ActorRoot->SetMobility(EComponentMobility::Movable);
		
		WorldStartPos = Owner->GetTransform().TransformPosition(LocalStartPos);
		WorldEndPos = Owner->GetTransform().TransformPosition(LocalEndPos);
	}
}
// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!GetOwner()) return;

	FVector CurrentPos = GetOwner()->GetActorLocation();
	FVector TargetPos = bMovingToEnd ? WorldEndPos : WorldStartPos;
	FVector Direction = (TargetPos - CurrentPos).GetSafeNormal();
	FVector NewPos = CurrentPos + MovementSpeed * DeltaTime * Direction;
	
	if (FVector::Dist(NewPos, TargetPos) < FVector::Dist(CurrentPos, TargetPos)){
		GetOwner()->SetActorLocation(NewPos);
	}else{
		GetOwner()->SetActorLocation(TargetPos);
		bMovingToEnd = !bMovingToEnd;
	}
}

