#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueDataAsset.h"
#include "DialogueComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueLine, FText, Line);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueChoiceRequested, const TArray<FDialogueChoice>&, Choices);
	
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIDEQUEST_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDialogueComponent();

	void Interact(UDialogueDataAsset* Dialogue);
	void StartDialogue(UDialogueDataAsset* Dialogue);
	void EndDialogue();
	void SelectChoice(int32 ChoiceIndex);

	UPROPERTY(BlueprintAssignable)
	FOnDialogueLine OnDialogueLine;

	UPROPERTY(BlueprintAssignable)
	FOnDialogueFinished OnDialogueFinished;

	UPROPERTY(BlueprintAssignable)
	FOnDialogueChoiceRequested OnDialogueChoiceRequested;

	//UPROPERTY(BlueprintAssignable)
	//FOnDialogueChoices OnDialogueChoices;

	void SetIsInDialogue(bool bNewValue);
	bool IsInDialogue() { return bIsInDialogue; }

protected:
	virtual void BeginPlay() override;
	virtual void PostInitProperties() override;

	
	UPROPERTY(VisibleAnywhere, Category = "Dialogue")
	bool bDialogueFinished = false;

	UPROPERTY(VisibleAnywhere, Category = "Dialogue")
	bool bIsInDialogue = false;

	UPROPERTY(VisibleAnywhere, Category = "Dialogue")
	bool bWaitingForChoice = false;

	UPROPERTY(VisibleAnywhere, Category = "Dialogue")
	UDialogueDataAsset* CurrentDialogue;

	UPROPERTY(VisibleAnywhere, Category = "Dialogue")
	int32 CurrentIndex = 0;
private:
	//FName CurrentNodeID;

	//const FDialogueNode* GetNode(FName NodeID) const;
	//void ProcessCurrentNode();
	void ProcessCurrentLine();
	//void NextNode();
};
