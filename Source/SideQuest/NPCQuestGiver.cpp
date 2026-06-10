#include "NPCQuestGiver.h"

void ANPCQuestGiver::Interact(AActor* Interactor)
{
	Super::Interact(Interactor);

	if (bQuestGiven) return;

	bQuestGiven = true;

	UE_LOG(LogTemp, Warning, TEXT("Quest Started: %s"), *QuestID.ToString());
}