// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable.h"

#include "LanderGameMode.h"
#include "Ship.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACollectable::ACollectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollectableMesh = CreateDefaultSubobject<UStaticMeshComponent>("CollectableMesh");
	SetRootComponent(CollectableMesh);

	
}

// Called when the game starts or when spawned
void ACollectable::BeginPlay()
{
	Super::BeginPlay();
	CollectableMesh->OnComponentBeginOverlap.AddDynamic(this, &ACollectable::OnOverlapBegin);
	CollectableMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

// Called every frame
void ACollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
void ACollectable::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){

	if (OtherActor && OtherActor->IsA(AShip::StaticClass())){
		Collect();
	}
}
void ACollectable::Collect(){
	if (ALanderGameMode* LanderGameMode = Cast<ALanderGameMode>(UGameplayStatics::GetGameMode(this))){
		LanderGameMode->IncreaseTimer(TimeToAdd);
		Destroy();
	}
}
