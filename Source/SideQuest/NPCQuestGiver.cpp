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

	UQuestManagerComponent* QuestManager = Player->GetQuestManager();
	if (!QuestManager) return;

	UUIManagerComponent* UIManager = Player->GetUIManager();
	if (!UIManager) return;

	UDialogueComponent* DialogueComponent = Player->GetDialogueComponent();
	if (!DialogueComponent) return;

	const FQuestData& Quest = QuestData;

	EQuestState State = GetQuestState(Player);
	UDialogueDataAsset* const* FoundDialogue = DialogueMap.Find(State);

	if (FoundDialogue && *FoundDialogue)
	{
		CurrentDialogueAsset = *FoundDialogue;
	}
	else
	{
		CurrentDialogueAsset = nullptr;
	}

	UDialogueWidget* Widget = Cast<UDialogueWidget>(UIManager->GetWidget("Dialogue"));
	if (!Widget)
	{
		UE_LOG(LogTemp, Warning, TEXT("Widget not valid"));
		return;
	}

	if (!DialogueComponent->GetCurrentQuestGiver())
	{
		DialogueComponent->SetQuestGiver(this);
	}

	if (!DialogueComponent->IsInDialogue())
	{
		Widget->InitializeWidget(DialogueComponent);
		UIManager->ShowWidget("Dialogue");
	}

	DialogueComponent->Interact(CurrentDialogueAsset);
}

EQuestState ANPCQuestGiver::GetQuestState(ACustomPlayerCharacter* Player)
{
	UQuestManagerComponent* QM = Player->GetQuestManager();

	if (QM->IsQuestCompleted(QuestData.QuestID))
	{
		return EQuestState::TurnedIn;
	}

	if (QM->HasQuest(QuestData.QuestID))
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