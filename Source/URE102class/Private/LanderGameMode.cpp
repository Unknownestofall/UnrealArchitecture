// Fill out your copyright notice in the Description page of Project Settings.


#include "LanderGameMode.h"

#include "Ship.h"
#include "Data/LevelTimerData.h"
#include "Kismet/GameplayStatics.h"

ALanderGameMode::ALanderGameMode(){
	PrimaryActorTick.bCanEverTick = true;
	//CountdownTimer = 30.f;

	static ConstructorHelpers::FObjectFinder<UDataTable>
		DataTableAsset(TEXT("/Script/Engine.DataTable'/Game/DataTables/LevelTimerData.LevelTimerData'"));

	if (DataTableAsset.Succeeded()){
		UE_LOG(LogTemp, Warning, TEXT("DT Loaded"));
		LevelTimerDataTable = DataTableAsset.Object;
	}else{
		UE_LOG(LogTemp, Warning, TEXT("did not find DT "));
	}
	DefaultPawnClass = AShip::StaticClass();
}
void ALanderGameMode::BeginPlay(){
	Super::BeginPlay();
	if (LevelTimerDataTable != nullptr){
		FName CurLevelName = *UGameplayStatics::GetCurrentLevelName(this);

		for (auto It : LevelTimerDataTable->GetRowMap()){
			const FLevelTimerData* Row = reinterpret_cast<const FLevelTimerData*>(It.Value);
			if (Row->LevelName == CurLevelName){
				CountdownTimer = Row->TimerValue;
			}
		}
	}
	Timer = CountdownTimer;
	APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerController){
		FName CurLevelName = *UGameplayStatics::GetCurrentLevelName(this);
		if (CurLevelName == "MainMenu"){
			PlayerController->bShowMouseCursor = true;
			PlayerController->SetInputMode(FInputModeUIOnly());
		}else{
			PlayerController->bShowMouseCursor = false;
			PlayerController->SetInputMode(FInputModeGameOnly());
		}
	}
}
void ALanderGameMode::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	
	if (bIsTimerRunning){
		if (Timer > 0)
		{
			Timer -= DeltaTime;
			if (Timer <= 0.f){
				FName CurOpenLevel = *UGameplayStatics::GetCurrentLevelName(this);
				UGameplayStatics::OpenLevel(this, CurOpenLevel);
			}
		}
	}
	if (GEngine){
		GEngine->AddOnScreenDebugMessage(2,INDEFINITELY_LOOPING_DURATION, FColor::Blue,
			FString::Printf(TEXT("Time Remaining: %f"),Timer));
	}
}
void ALanderGameMode::IncreaseTimer(float TimeToAdd){
	Timer += TimeToAdd;
}
void ALanderGameMode::StopTimer(){
	bIsTimerRunning = false;
}
void ALanderGameMode::LoadNextLevel(){
	int32 StartingLevel = GetCurLevelID();
	if (StartingLevel != -1){
		for (auto It : LevelTimerDataTable->GetRowMap()){
			const FLevelTimerData* Row = reinterpret_cast<const FLevelTimerData*>(It.Value);
			if (Row && Row->LevelID == (StartingLevel + 1)){
				UGameplayStatics::OpenLevel(this, Row->LevelName);
				return;
			}
		}
	}
}
int32 ALanderGameMode::GetCurLevelID() const{
	FName CurLevelName = *UGameplayStatics::GetCurrentLevelName(this);

	for (auto It : LevelTimerDataTable->GetRowMap()){
		const FLevelTimerData* Row = reinterpret_cast<const FLevelTimerData*>(It.Value);
		if (Row->LevelName == CurLevelName){
			return Row->LevelID;
		}
	} return -1;
}


// increase timer func (timer to add)