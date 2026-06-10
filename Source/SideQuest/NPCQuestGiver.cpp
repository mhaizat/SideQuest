#include "NPCQuestGiver.h"

void ANPCQuestGiver::Interact(AActor* Interactor)
{
	ACustomPlayerCharacter* Player = Cast<ACustomPlayerCharacter>(Interactor);
	if (!Player) return;

	UQuestManagerComponent* QM = Player->GetQuestManager();
	if (!QM) return;
	
	const FName QuestID = QuestData.QuestID;

	// CASE 1: quest not started
	if (!QM->HasQuest(QuestID))
	{
		QM->StartQuest(QuestID);
		UE_LOG(LogTemp, Warning, TEXT("Quest Started: %s"), *QuestID.ToString());
		return;
	}

	// CASE 2: quest completed
	if (QM->IsQuestCompleted(QuestID))
	{
		UE_LOG(LogTemp, Warning, TEXT("Quest Turned In: %s"), *QuestID.ToString());

		QM->CompleteQuest(QuestID); // reward + cleanup
		return;
	}

	// CASE 3: in progress
	UE_LOG(LogTemp, Warning, TEXT("Quest in progress..."));
}