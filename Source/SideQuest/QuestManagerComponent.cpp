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
	for (const FQuestData& Quest : ActiveQuests)
	{
		if (Quest.QuestID == QuestID)
		{
			return true;
		}
	}

	return false;
}

void UQuestManagerComponent::StartQuest(FName QuestID)
{
	if (HasQuest(QuestID) || IsQuestCompleted(QuestID))
	{
		return;
	}

	FQuestData NewQuest;
	NewQuest.QuestID = QuestID;
	NewQuest.CurrentAmount = 0;
	NewQuest.bCompleted = false;

	NewQuest.ObjectiveId = QuestID;

	// IMPORTANT:
	// You should normally load ObjectiveID + RequiredAmount from a data table later
	// For now we assume QuestID == ObjectiveID OR you set it manually elsewhere

	ActiveQuests.Add(NewQuest);

	UE_LOG(LogTemp, Warning, TEXT("Quest Started: %s"), *QuestID.ToString());
}

bool UQuestManagerComponent::IsQuestCompleted(FName QuestID) const
{
	return CompletedQuests.Contains(QuestID);
}

void UQuestManagerComponent::AddProgress(FName ItemID, int32 Amount)
{
	for (FQuestData& Quest : ActiveQuests)
	{
		if (Quest.bCompleted || Quest.ObjectiveId != ItemID) continue;

		Quest.CurrentAmount += Amount;

		UE_LOG(LogTemp, Warning, TEXT("%s Progress %d/%d"), *Quest.QuestID.ToString(), Quest.CurrentAmount, Quest.RequiredAmount);
			
		if (Quest.CurrentAmount >= Quest.RequiredAmount)
		{
			Quest.bCompleted = true;

			CompletedQuests.AddUnique(Quest.QuestID);

			UE_LOG(LogTemp, Warning, TEXT("QUEST COMPLETE: %s"), *Quest.QuestID.ToString());
		}

		return;
	}
}

bool UQuestManagerComponent::HasRelevantQuest(FName ItemID) const
{
	for (const FQuestData& Quest : ActiveQuests)
	{
		if (!Quest.bCompleted && Quest.ObjectiveId == ItemID) return true;
	}

	return false;
}

void UQuestManagerComponent::CompleteQuest(FName QuestID)
{
	for (int32 i = 0; i < ActiveQuests.Num(); i++)
	{
		if (ActiveQuests[i].QuestID == QuestID)
		{
			UE_LOG(LogTemp, Warning, TEXT("Quest Completed (Turn-in): %s"), *QuestID.ToString());

			ActiveQuests.RemoveAt(i);
			break;
		}
	}

	CompletedQuests.AddUnique(QuestID);
}