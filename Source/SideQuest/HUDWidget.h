#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestTrackerWidget.h"
#include "Components/SizeBox.h"
#include "HUDWidget.generated.h"

class UUIManagerComponent;

UCLASS()
class SIDEQUEST_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	UQuestTrackerWidget* GetQuestTrackerWidget() const { return QuestTrackerWidget; }

	void InitializeHUDWidget(UUIManagerComponent* InUIManagerComponent);

protected:
	UPROPERTY()
	UQuestTrackerWidget* QuestTrackerWidget;

	UPROPERTY(meta = (BindWidget))
	USizeBox* SB_Quest;

	UPROPERTY()
	UUIManagerComponent* UIManagerComponent;

};
