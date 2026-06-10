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

void UQuestManagerComponent::AddProgress(FName ItemID, int32 Amount)
{
	for (FQuestData& Quest : ActiveQuests)
	{
		// ❌ ignore completed quests
		if (Quest.bCompleted)
		{
			continue;
		}

		// ❌ only relevant quests
		if (Quest.ObjectiveId != ItemID)
		{
			continue;
		}

		Quest.CurrentAmount += Amount;

		UE_LOG(LogTemp, Warning,
			TEXT("%s Progress %d/%d"),
			*Quest.QuestID.ToString(),
			Quest.CurrentAmount,
			Quest.RequiredAmount);

		if (Quest.CurrentAmount >= Quest.RequiredAmount)
		{
			Quest.bCompleted = true;

			CompletedQuests.AddUnique(Quest.QuestID);

			UE_LOG(LogTemp, Warning,
				TEXT("QUEST COMPLETE: %s"),
				*Quest.QuestID.ToString());
		}

		// IMPORTANT: stop after matching quest
		return;
	}
}

bool UQuestManagerComponent::HasRelevantQuest(FName ItemID) const
{
	for (const FQuestData& Quest : ActiveQuests)
	{
		if (!Quest.bCompleted && Quest.ObjectiveId == ItemID)
		{
			return true;
		}
	}

	return false;
}