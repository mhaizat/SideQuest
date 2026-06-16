#pragma once

#include "CoreMinimal.h"
#include "DialogueData.generated.h"

UENUM(BlueprintType)
enum class EDialogueAction : uint8
{
	None,
	StartQuest,
	OngoingQuest,
	CompleteQuest
};

USTRUCT(BlueprintType)
struct FDialogueChoice
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NextIndex = INDEX_NONE;
};

USTRUCT(BlueprintType)
struct FDialogueNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDialogueAction Action = EDialogueAction::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsEnd = false;

	// NEW: default next node
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NextIndex = INDEX_NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDialogueChoice> Choices;
};

USTRUCT(BlueprintType)
struct FDialogueData
{
    GENERATED_BODY()

    /*UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName StartNodeID;*/

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FDialogueNode> Nodes;
};
