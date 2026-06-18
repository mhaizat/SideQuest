#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestData.h"
#include "DialogueData.h"
#include "QuestManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestStarted, FQuestData, Quest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestUpdated, FQuestData, Quest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestCompleted, FQuestData, Quest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIDEQUEST_API UQuestManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UQuestManagerComponent();

	void AddQuest(const FQuestData& Quest);
	void AddProgress(FName ItemID, int32 Amount = 1);
	bool HasRelevantQuest(FName ItemID) const;
	bool HasQuest(FName QuestID) const;
	bool IsQuestCompleted(FName QuestID) const;
	void StartQuest(const FQuestData& QuestData);
	void CompleteQuest(FName QuestID);

	UPROPERTY(BlueprintAssignable)
	FOnQuestStarted OnQuestStarted;

	UPROPERTY(BlueprintAssignable)
	FOnQuestUpdated OnQuestUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnQuestCompleted OnQuestCompleted;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<FQuestData> ActiveQuests;

	UPROPERTY()
	TArray<FName> CompletedQuests;
};
