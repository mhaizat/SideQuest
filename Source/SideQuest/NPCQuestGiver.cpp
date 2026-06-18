#include "NPCQuestGiver.h"
#include "QuestManagerComponent.h"
#include "CustomPlayerCharacter.h"
#include "UIManagerComponent.h"
#include "DialogueComponent.h"
#include "DialogueWidget.h"

void ANPCQuestGiver::BeginPlay()
{
	Super::BeginPlay();
}

void ANPCQuestGiver::Interact(AActor* Interactor)
{
	Super::Interact(Interactor);

	ACustomPlayerCharacter* Player = Cast<ACustomPlayerCharacter>(Interactor);
	if (!Player) return;

	UUIManagerComponent* UIManagerComponent = Player->GetUIManager();
	if (!UIManagerComponent) return;

	UDialogueComponent* DialogueComponent = Player->GetDialogueComponent();
	if (!DialogueComponent) return;

	const FQuestData& Quest = QuestData;

	EQuestState State = GetQuestState(Player);

	UDialogueDataAsset* const* FoundDialogue = DialogueMap.Find(State);
	CurrentDialogueAsset = (FoundDialogue && *FoundDialogue) ? *FoundDialogue : nullptr;

	UDialogueWidget* Widget = Cast<UDialogueWidget>(UIManagerComponent->GetWidget("Dialogue"));
	if (!Widget) return;

	if (!DialogueComponent->GetCurrentQuestGiver())
	{
		DialogueComponent->SetQuestGiver(this);
	}

	if (!DialogueComponent->IsInDialogue())
	{
		Widget->InitializeWidget(DialogueComponent);
		UIManagerComponent->ShowWidget("Dialogue");
	}

	DialogueComponent->Interact(CurrentDialogueAsset);
}

EQuestState ANPCQuestGiver::GetQuestState(ACustomPlayerCharacter* Player)
{
	UQuestManagerComponent* QuestManagerComponent = Player->GetQuestManager();

	if (QuestManagerComponent->IsQuestCompleted(QuestData.QuestID))
	{
		QuestManagerComponent->OnQuestCompleted.Broadcast(QuestData);
		return EQuestState::TurnedIn;
	}

	if (QuestManagerComponent->HasQuest(QuestData.QuestID))
	{
		return EQuestState::InProgress;
	}

	return EQuestState::NotOffered;
}

void ANPCQuestGiver::OnPlayerEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPlayerEnter(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void ANPCQuestGiver::OnPlayerExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnPlayerExit(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
}