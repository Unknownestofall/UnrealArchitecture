// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomTrigger.h"

#include "Components/BoxComponent.h"

// Sets default values for this component's properties
UCustomTrigger::UCustomTrigger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCustomTrigger::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* ParentActor = GetOwner()){
		if (UBoxComponent* BoxComponent = ParentActor->FindComponentByClass<UBoxComponent>()){
			BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &UCustomTrigger::OnOverlapBegin);
		}
	}
	
}


// Called every frame
void UCustomTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UCustomTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
	if (OtherActor && OtherActor != GetOwner()){
		//TODO: restart level
		UE_LOG(LogTemp, Error, TEXT("Out of bounds!"));
	}
}