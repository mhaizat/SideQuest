#include "NPCQuestGiver.h"
#include "QuestManagerComponent.h"
#include "CustomPlayerCharacter.h"
#include "UIManagerComponent.h"
#include "DialogueComponent.h"

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

	DialogueComponent->Interact(DialogueData);

	const FName QuestID = QuestData.QuestID;

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

void ANPCQuestGiver::OnPlayerEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPlayerEnter(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	UE_LOG(LogTemp, Warning, TEXT("Quest NPC Enter"));
}

void ANPCQuestGiver::OnPlayerExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnPlayerExit(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);

	UE_LOG(LogTemp, Warning, TEXT("Quest NPC Exit"));
}