#pragma once

#include "CoreMinimal.h"
#include "QuestData.generated.h"

USTRUCT(BlueprintType)
struct FQuestData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName QuestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RequiredAmount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TargetItemID;
};