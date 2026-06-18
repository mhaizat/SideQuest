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

void UQuestManagerComponent::StartQuest(const FQuestData& QuestData)
{
	if (HasQuest(QuestData.QuestID) || IsQuestCompleted(QuestData.QuestID))
	{
		return;
	}

	FQuestData NewQuest = QuestData;
	NewQuest.CurrentAmount = 0;
	NewQuest.bCompleted = false;

	ActiveQuests.Add(NewQuest);

	UE_LOG(LogTemp, Warning, TEXT("Quest Started: %s"), *QuestData.QuestID.ToString());
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

			ActiveQuests.RemoveAll([&](const FQuestData& Q)
			{
				return Q.QuestID == Quest.QuestID;
			});

			UE_LOG(LogTemp, Warning, TEXT("QUEST COMPLETE: %s"), *Quest.QuestID.ToString());
		}

		OnQuestUpdated.Broadcast(Quest);

		UE_LOG(LogTemp, Warning, TEXT("ItemID: '%s'"), *ItemID.ToString());
		UE_LOG(LogTemp, Warning, TEXT("Quest Objective: '%s'"), *Quest.ObjectiveId.ToString());

		return;
	}
}

bool UQuestManagerComponent::HasRelevantQuest(FName ItemID) const
{
	for (const FQuestData& Quest : ActiveQuests)
	{
		if (!Quest.bCompleted && Quest.ObjectiveId == ItemID)
		{
			UE_LOG(LogTemp, Warning, TEXT("Has Quest"));
			return true;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Doesnt have Quest"));
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
