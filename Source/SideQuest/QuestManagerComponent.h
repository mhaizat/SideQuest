#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestData.h"
#include "QuestManagerComponent.generated.h"

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
	void StartQuest(FName QuestID);
	void CompleteQuest(FName QuestID);

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<FQuestData> ActiveQuests;

	UPROPERTY()
	TArray<FName> CompletedQuests;
};
