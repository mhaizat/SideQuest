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

	//OnDialogueFinished.Broadcast();
}

void UDialogueComponent::ProcessCurrentLine()
{
	/*if (!CurrentDialogue)
	{
		EndDialogue();
		return;
	}*/
	
	if (!CurrentDialogue->Nodes.IsValidIndex(CurrentIndex))
	{
		EndDialogue();
		UE_LOG(LogTemp, Warning, TEXT("ProcessCurrentLine 1"));

		return;
	}
	
	const FDialogueNode& Node = CurrentDialogue->Nodes[CurrentIndex];

	OnDialogueLine.Broadcast(Node.Text);

	if (Node.bIsEnd)
	{
		bDialogueFinished = true;

		UE_LOG(LogTemp, Warning, TEXT("ProcessCurrentLine 2"));

		return;
	}

	CurrentIndex++;
}

//void UDialogueComponent::SelectChoice(int32 ChoiceIndex)
//{
//	const FDialogueNode* CurrentNode = GetNode(CurrentNodeID);
//	if (!CurrentNode)
//	{
//		EndDialogue();
//		return;
//	}
//
//	if (!CurrentNode->Choices.IsValidIndex(ChoiceIndex))
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Invalid dialogue choice index"));
//		return;
//	}
//
//	const FDialogueChoice& Choice = CurrentNode->Choices[ChoiceIndex];
//
//	CurrentNodeID = Choice.NextNodeID;
//
//	ProcessCurrentNode();
//}

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