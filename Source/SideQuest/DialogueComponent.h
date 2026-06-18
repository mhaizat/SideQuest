#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueDataAsset.h"
#include "DialogueComponent.generated.h"

class ANPCQuestGiver;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueLine, FText, Line);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueChoiceRequested, const TArray<FDialogueChoice>&, Choices);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDialogueAction, EDialogueAction, Action, FName, QuestID);
	
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIDEQUEST_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:
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

	UPROPERTY(BlueprintAssignable)
	FOnDialogueAction OnDialogueAction;

	void SetIsInDialogue(bool bNewValue);
	bool IsInDialogue() { return bIsInDialogue; }

	ANPCQuestGiver* GetCurrentQuestGiver() { return CurrentQuestGiver; }
	void SetQuestGiver(ANPCQuestGiver* InQuestGiver);

protected:
	virtual void BeginPlay() override;
	virtual void PostInitProperties() override;

	void ExecuteDialogueAction(EDialogueAction Action);
	
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

	UPROPERTY()
	ANPCQuestGiver* CurrentQuestGiver = nullptr;

private:
	void ProcessCurrentLine();
};
