// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AShip::AShip(){
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	SetRootComponent(ShipMesh);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(ShipMesh);
	CameraBoom->TargetArmLength = 1000.f;
	
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	ViewCamera->SetupAttachment(CameraBoom);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AShip::BeginPlay(){
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())){
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())){
			Subsystem->AddMappingContext(ShipMappingContext, 0);
		}
	}
}

// Called every frame
void AShip::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	if (GEngine)
	{
		CurrentVelocity = GetVelocity().Length();
		GEngine->AddOnScreenDebugMessage(1,
			INDEFINITELY_LOOPING_DURATION,
			FColor::Red,
			FString::Printf(TEXT("CurrentVelocity: %f"), CurrentVelocity));
	}
}

// Called to bind functionality to input
void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)){
		EnhancedInput->BindAction(PropelUpAction, ETriggerEvent::Triggered, this, &AShip::PropelUp);
		EnhancedInput->BindAction(ShipRotationAction, ETriggerEvent::Triggered, this, &AShip::ShipRotation);
	}
}
void AShip::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit){

	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	HandleShipLanding();
}
void AShip::PropelUp(const FInputActionValue& Value){
	if (!bIsInputEnabled){ return; }
	
	if (bool CurrentValue = Value.Get<bool>()){
		const FVector WorldImpulseVector = FVector(0,0,1) * ImpulseStrength;
		const FVector LocalImpulse = GetActorRotation().RotateVector(WorldImpulseVector);
		ShipMesh->AddImpulse(LocalImpulse, NAME_None,true);
	}
}
void AShip::ShipRotation(const FInputActionValue& Value){
	if (!bIsInputEnabled){ return; }
	if (float CurrentValue = Value.Get<float>()){
		const FVector Torque = FVector(1,0,0) * CurrentValue * TorqueStrength;
		ShipMesh->AddTorqueInRadians(Torque, NAME_None, true);
	}
}
bool AShip::IsLandedSafely(){
	FRotator CurrentRotation = GetActorRotation();
	float AcceptableRollRange = 70.f;

	return FMath::Abs(CurrentRotation.Roll) <= AcceptableRollRange;
}
void AShip::HandleShipLanding(){
	if (!IsLandedSafely() || CurrentVelocity > MaxLandingVelocity ){
		FName CurrentLevelName = *UGameplayStatics::GetCurrentLevelName(this,true);
		UGameplayStatics::OpenLevel(GetWorld(), CurrentLevelName,false);
	}else{
		UE_LOG(LogTemp, Warning, TEXT("Safe land"));	
	}
}
void AShip::IsGoalReached(){
	bIsInputEnabled = false;
}

