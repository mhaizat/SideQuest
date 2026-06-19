#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestTrackerWidget.h"
#include "NotificationWidget.h"
#include "Components/SizeBox.h"
#include "HUDWidget.generated.h"

class UUIManagerComponent;
class UQuestManagerComponent;

UCLASS()
class SIDEQUEST_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable)
	UQuestTrackerWidget* GetQuestTrackerWidget() const { return QuestTrackerWidget; }

	void InitializeHUDWidget(UUIManagerComponent* InUIManagerComponent);

	void SetBindingDelegates();

protected:
	UPROPERTY()
	UQuestTrackerWidget* QuestTrackerWidget;
	UPROPERTY()
	UNotificationWidget* NotificationWidget;

	UPROPERTY(meta = (BindWidget))
	USizeBox* SB_Quest;

	UPROPERTY(meta = (BindWidget))
	USizeBox* SB_Notification;

	UFUNCTION()
	void ShowNotificationWidget(bool bVisible);

	UPROPERTY()
	UUIManagerComponent* UIManagerComponent;

	UPROPERTY()
	UQuestManagerComponent* QuestManagerComponent;

};
