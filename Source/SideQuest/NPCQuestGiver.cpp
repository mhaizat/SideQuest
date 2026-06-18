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
		CurrentDialogueAsset = nullptr; // or fallback dialogue
	}

	UDialogueWidget* Widget = Cast<UDialogueWidget>(UIManager->GetWidget("Dialogue"));
	if (!Widget) return;

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


	//if (bQuestGiven)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Quest is in progress"));
	//	return;
	//}

	//if (QuestManager->IsQuestCompleted(Quest.QuestID))
	//{
	//	QuestManager->CompleteQuest(Quest.QuestID);
	//	UE_LOG(LogTemp, Warning, TEXT("Player has completed quest - should use turn-in dialogue"));
	//	bQuestGiven = false;
	//	return;
	//	// OPTIONAL: switch to turn-in dialogue asset
	//	// DialogueAsset = TurnInDialogueAsset;
	//}

	//UDialogueWidget* Widget = Cast<UDialogueWidget>(UIManager->GetWidget("Dialogue"));
	//if (!Widget) return;

	//if (!DialogueComponent->GetCurrentQuestGiver())
	//{
	//	DialogueComponent->SetQuestGiver(this);
	//}

	//if (!DialogueComponent->IsInDialogue())
	//{
	//	Widget->InitializeWidget(DialogueComponent);
	//	UIManager->ShowWidget("Dialogue");
	//}

	//DialogueComponent->Interact(DialogueAsset);

	//const FName QuestID = QuestData.QuestID;

	/*if (QuestManager->IsQuestCompleted(QuestID))
	{
		QuestManager->CompleteQuest(QuestID);
		bQuestGiven = false;

		UE_LOG(LogTemp, Warning, TEXT("Quest Turned In: %s"), *QuestID.ToString());
		return;
	}

	if (bQuestGiven)
	{
		UE_LOG(LogTemp, Warning, TEXT("Quest already given, in progress..."));
		return;
	}

	if (!QuestManager->HasQuest(QuestID))
	{
		QuestManager->StartQuest(QuestData);
		bQuestGiven = true;

		UIManager->SetUIState(EUIState::Quest);

		UQuestTrackerWidget* Widget = Cast<UQuestTrackerWidget>(UIManager->GetWidget("Quest"));
		if (!Widget) return;

		Widget->InitializeQuestDisplay(QuestData);

		UE_LOG(LogTemp, Warning, TEXT("Quest Started: %s"), *QuestID.ToString());
		return;
	}*/
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