#include "QuestManagerComponent.h"

UQuestManagerComponent::UQuestManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UQuestManagerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UQuestManagerComponent::AddQuest(const FQuestData& Quest)
{
    if (HasQuest(Quest.QuestID))
    {
        UE_LOG(LogTemp, Warning, TEXT("Quest already active"));
        return;
    }

    ActiveQuests.Add(Quest);

    UE_LOG(LogTemp, Warning, TEXT("Quest Accepted: %s"), *Quest.QuestID.ToString());
}

bool UQuestManagerComponent::HasQuest(FName QuestID) const
{
	for (const FQuestData& Q : ActiveQuests)
	{
		if (Q.QuestID == QuestID) return true;
	}

	return false;
}