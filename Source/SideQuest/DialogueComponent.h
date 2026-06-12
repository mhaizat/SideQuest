#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueData.h"
#include "DialogueComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueLine, FText, Line);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueFinished);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIDEQUEST_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDialogueComponent();

	void Interact(const FDialogueData& Dialogue);
	void StartDialogue(const FDialogueData& Dialogue);
	void NextLine();
	void EndDialogue();

	UPROPERTY(BlueprintAssignable)
	FOnDialogueLine OnDialogueLine;

	UPROPERTY(BlueprintAssignable)
	FOnDialogueFinished OnDialogueFinished;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	bool bIsInDialogue = false;

private:
	UPROPERTY()
	FDialogueData CurrentDialogue;

	int32 CurrentIndex = 0;
};
