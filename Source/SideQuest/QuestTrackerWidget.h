#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "QuestData.h"
#include "QuestTrackerWidget.generated.h"

class UQuestManagerComponent;

UCLASS()
class SIDEQUEST_API UQuestTrackerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void HandleQuestUpdated(FQuestData Quest);
	UFUNCTION()
	void InitializeQuestDisplay(FQuestData Quest);
	UFUNCTION()
	void HandleQuestCompleted(FQuestData Quest);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuestNameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ProgressText;

private:

	UQuestManagerComponent* CachedQuestManager;
};
