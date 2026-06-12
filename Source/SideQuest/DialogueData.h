#pragma once

#include "CoreMinimal.h"
#include "DialogueData.generated.h"

USTRUCT(BlueprintType)
struct FDialogueLine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEndDialogue = false;
};

USTRUCT(BlueprintType)
struct FDialogueData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName DialogueID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDialogueLine> Lines;
};

USTRUCT(BlueprintType)
struct FDialogueNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FText Text;

	UPROPERTY(EditAnywhere)
	TArray<FName> NextNodeIDs; // branching

	UPROPERTY(EditAnywhere)
	bool bIsEnd = false;
};