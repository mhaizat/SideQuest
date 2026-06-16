#include "DialogueComponent.h"

UDialogueComponent::UDialogueComponent()
{
}

void UDialogueComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDialogueComponent::SetIsInDialogue(bool bNewValue)
{
	bIsInDialogue = bNewValue;
}

void UDialogueComponent::PostInitProperties()
{
	Super::PostInitProperties();
	SetIsInDialogue(false);
}

void UDialogueComponent::Interact(UDialogueDataAsset* Dialogue)
{
	if (bDialogueFinished)
	{
		EndDialogue();
		OnDialogueFinished.Broadcast();
		bDialogueFinished = false;
		return;
	}

	if (!bIsInDialogue)
	{
		StartDialogue(Dialogue);
		return;
	}

	ProcessCurrentLine();
}

void UDialogueComponent::StartDialogue(UDialogueDataAsset* Dialogue)
{
	UE_LOG(LogTemp, Warning, TEXT("StartDialogue"));

	CurrentDialogue = Dialogue;
	CurrentIndex = 0;
	SetIsInDialogue(true);

	ProcessCurrentLine();
}

void UDialogueComponent::EndDialogue()
{
	UE_LOG(LogTemp, Warning, TEXT("Dialogue Ended"));

	SetIsInDialogue(false);
	CurrentDialogue = nullptr;
	CurrentIndex = 0;

	bIsInDialogue = false;
	bWaitingForChoice = false;

	OnDialogueChoiceRequested.Broadcast(TArray<FDialogueChoice>());
	OnDialogueLine.Broadcast(FText::FromString(TEXT("")));

	//OnDialogueFinished.Broadcast();
}

void UDialogueComponent::ProcessCurrentLine()
{
	if (!CurrentDialogue ||
		!CurrentDialogue->Nodes.IsValidIndex(CurrentIndex))
	{
		EndDialogue();
		return;
	}

	const FDialogueNode& Node = CurrentDialogue->Nodes[CurrentIndex];

	// Always show text
	OnDialogueLine.Broadcast(Node.Text);

	// 🔥 END NODE → CLEAR UI
	if (Node.bIsEnd)
	{
		bDialogueFinished = true;

		// IMPORTANT: clear choices UI
		OnDialogueChoiceRequested.Broadcast(TArray<FDialogueChoice>());

		return;
	}

	// CHOICE NODE
	if (Node.Choices.Num() > 0)
	{
		bWaitingForChoice = true;
		OnDialogueChoiceRequested.Broadcast(Node.Choices);
		return;
	}

	// NORMAL FLOW
	if (Node.NextIndex != INDEX_NONE)
	{
		CurrentIndex = Node.NextIndex;
	}
	else
	{
		CurrentIndex++;
	}
}

void UDialogueComponent::SelectChoice(int32 ChoiceIndex)
{
	if (!bWaitingForChoice) return;

	const FDialogueNode& Node = CurrentDialogue->Nodes[CurrentIndex];

	if (!Node.Choices.IsValidIndex(ChoiceIndex)) return;

	const int32 NextNodeIndex = Node.Choices[ChoiceIndex].NextIndex;

	if (NextNodeIndex == INDEX_NONE) return;

	CurrentIndex = NextNodeIndex;

	bWaitingForChoice = false;

	OnDialogueChoiceRequested.Broadcast(TArray<FDialogueChoice>());

	ProcessCurrentLine();
}

//const FDialogueNode* UDialogueComponent::GetNode(FName NodeID) const
//{
//	for (const FDialogueNode& Node : CurrentDialogue->Nodes)
//    {
//        if (Node.NodeID == NodeID)
//        {
//            return &Node;
//        }
//    }
//
//    return nullptr;
//}