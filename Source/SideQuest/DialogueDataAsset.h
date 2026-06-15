#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DialogueData.h"
#include "DialogueDataAsset.generated.h"

UCLASS(BlueprintType)
class SIDEQUEST_API UDialogueDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//FName StartNodeID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FDialogueNode> Nodes;
};
