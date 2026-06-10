#include "NPCQuestGiver.h"

void ANPCQuestGiver::Interact(AActor* Interactor)
{
	ACustomPlayerCharacter* Player = Cast<ACustomPlayerCharacter>(Interactor);
	if (!Player) return;

	UQuestManagerComponent* QuestManager = Player->GetQuestManager();
	if (!QuestManager) return;
	
	const FName QuestID = QuestData.QuestID;

	//! NOTE: CASE 1: quest not started
	if (!QuestManager->HasQuest(QuestID))
	{
		QuestManager->StartQuest(QuestID);
		UE_LOG(LogTemp, Warning, TEXT("Quest Started: %s"), *QuestID.ToString());
		return;
	}

	//! NOTE: CASE 2: quest completed
	if (QuestManager->IsQuestCompleted(QuestID))
	{
		UE_LOG(LogTemp, Warning, TEXT("Quest Turned In: %s"), *QuestID.ToString());

		QuestManager->CompleteQuest(QuestID); // reward + cleanup
		return;
	}

	//! NOTE: CASE 3: in progress
	UE_LOG(LogTemp, Warning, TEXT("Quest in progress..."));
}