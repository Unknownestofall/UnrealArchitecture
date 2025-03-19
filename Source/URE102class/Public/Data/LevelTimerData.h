#pragma once

#include "CoreMinimal.h"
#include "LevelTimerData.generated.h"

USTRUCT(BlueprintType)
struct FLevelTimerData: public  FTableRowBase{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 LevelID = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName LevelName = NAME_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float TimerValue = 0.0f;

};
