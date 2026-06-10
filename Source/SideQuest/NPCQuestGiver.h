#pragma once

#include "CoreMinimal.h"
#include "NPCInteractable.h"
#include "QuestData.h"
#include "NPCQuestGiver.generated.h"

UCLASS()
class SIDEQUEST_API ANPCQuestGiver : public ANPCInteractable
{
	GENERATED_BODY()

public:
	virtual void Interact(AActor* Interactor) override;

protected:

	UPROPERTY(EditAnywhere)
	FName QuestID;

	UPROPERTY(EditAnywhere)
	bool bQuestGiven = false;

	UPROPERTY(EditAnywhere, Category = "Quest")
	FQuestData QuestData;
};
