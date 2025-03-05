// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "LanderGameMode.generated.h"

/**
 * 
 */
UCLASS()
class URE102CLASS_API ALanderGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ALanderGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION() void IncreaseTimer(float TimeToAdd);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	float CountdownTimer;
	
	void StopTimer();
	void LoadNextLevel();

protected:
	UPROPERTY() UDataTable* LevelTimerDataTable;
private:
	float Timer;
	bool bIsTimerRunning = true;
	int32 GetCurLevelID() const;
};
