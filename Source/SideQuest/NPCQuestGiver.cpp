#include "NPCQuestGiver.h"

void ANPCQuestGiver::Interact(AActor* Interactor)
{
    Super::Interact(Interactor);

    ACustomPlayerCharacter* Player = Cast<ACustomPlayerCharacter>(Interactor);
    if (!Player)return;

    UQuestManagerComponent* QuestManager = Player->GetQuestManager();
    if (!QuestManager) return;

    QuestManager->AddQuest(QuestData);
}