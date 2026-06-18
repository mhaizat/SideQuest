#include "DialogueComponent.h"
#include "GameStateManagerComponent.h"
#include "CustomPlayerCharacter.h"
#include "NPCQuestGiver.h"

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
	
	ACustomPlayerCharacter* Player = Cast<ACustomPlayerCharacter>(GetOwner());
	if (!Player) return;

	UGameStateManagerComponent* GameStateManagerComponent = Player->GetGameStateManagerComponent();
	if (!GameStateManagerComponent) return;

	GameStateManagerComponent->SetState(EGameState::UIOnly);

	CurrentDialogue = Dialogue;
	CurrentIndex = 0;
	SetIsInDialogue(true);

	ProcessCurrentLine();
}

void UDialogueComponent::EndDialogue()
{
	ACustomPlayerCharacter* Player = Cast<ACustomPlayerCharacter>(GetOwner());
	if (!Player) return;

	UGameStateManagerComponent* GameStateManagerComponent = Player->GetGameStateManagerComponent();
	if (!GameStateManagerComponent) return;

	GameStateManagerComponent->SetState(EGameState::Gameplay);

	UE_LOG(LogTemp, Warning, TEXT("Dialogue Ended"));

	SetIsInDialogue(false);
	CurrentDialogue = nullptr;
	CurrentIndex = 0;

	bIsInDialogue = false;
	bWaitingForChoice = false;

	OnDialogueChoiceRequested.Broadcast(TArray<FDialogueChoice>());
	OnDialogueLine.Broadcast(FText::FromString(TEXT("")));
}

void UDialogueComponent::ProcessCurrentLine()
{
	if (!CurrentDialogue || !CurrentDialogue->Nodes.IsValidIndex(CurrentIndex))
	{
		EndDialogue();
		return;
	}

	const FDialogueNode& Node = CurrentDialogue->Nodes[CurrentIndex];

	OnDialogueLine.Broadcast(Node.Text);

	if (Node.Action != EDialogueAction::None)
	{
		ExecuteDialogueAction(Node.Action);

	}

	if (Node.bIsEnd)
	{
		bDialogueFinished = true;

		OnDialogueChoiceRequested.Broadcast(TArray<FDialogueChoice>());

		return;
	}

	//! NOTE: CHOICE NODE
	if (Node.Choices.Num() > 0)
	{
		bWaitingForChoice = true;
		OnDialogueChoiceRequested.Broadcast(Node.Choices);
		return;
	}

	//! NOTE: NORMAL FLOW
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

void UDialogueComponent::ExecuteDialogueAction(EDialogueAction Action)
{
	if (!CurrentQuestGiver) return;

	ACustomPlayerCharacter* Player = Cast<ACustomPlayerCharacter>(GetOwner());
	if (!Player) return;

	UQuestManagerComponent* QuestManager = Player->GetQuestManager();
	if (!QuestManager) return;

	switch (Action)
	{
		case EDialogueAction::StartQuest:
		{
			QuestManager->StartQuest(GetCurrentQuestGiver()->GetQuestData());
			GetCurrentQuestGiver()->SetQuestGiven(true);
			break;
		}

		case EDialogueAction::CompleteQuest:
		{
			QuestManager->CompleteQuest(GetCurrentQuestGiver()->GetQuestData().QuestID);
			UE_LOG(LogTemp, Warning, TEXT("Quest completed"));

			break;
		}

		default:
			break;
	}
}

void UDialogueComponent::SetQuestGiver(ANPCQuestGiver* InQuestGiver)
{
	CurrentQuestGiver = InQuestGiver;
}
