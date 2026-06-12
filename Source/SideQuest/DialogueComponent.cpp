#include "DialogueComponent.h"

UDialogueComponent::UDialogueComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDialogueComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDialogueComponent::Interact(const FDialogueData& Dialogue)
{

	if (!bIsInDialogue)
	{
		StartDialogue(Dialogue);



		// FIRST LINE ALWAYS SAFE NOW
		OnDialogueLine.Broadcast(CurrentDialogue.Lines[0].Text);
		return;
	}

	NextLine();
}

void UDialogueComponent::StartDialogue(const FDialogueData& Dialogue)
{
	if (Dialogue.Lines.Num() == 0)
		return;

	CurrentDialogue = Dialogue;
	CurrentIndex = 0;
	bIsInDialogue = true;

	//OnDialogueLine.Broadcast(CurrentDialogue.Lines[0].Text);
}

void UDialogueComponent::NextLine()
{
	if (!bIsInDialogue)
		return;

	CurrentIndex++;

	// If no more lines → end dialogue
	if (!CurrentDialogue.Lines.IsValidIndex(CurrentIndex))
	{
		EndDialogue();
		return;
	}

	OnDialogueLine.Broadcast(CurrentDialogue.Lines[CurrentIndex].Text);
}

void UDialogueComponent::EndDialogue()
{
	bIsInDialogue = false;
	CurrentIndex = 0;
	CurrentDialogue.Lines.Empty(); // optional but safer

	OnDialogueFinished.Broadcast();
}