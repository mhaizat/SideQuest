#include "HUDWidget.h"
#include "CustomPlayerCharacter.h"
#include "GameFramework/Actor.h"

void UHUDWidget::InitializeHUD(UUIManagerComponent* InUIManagerComponent)
{
	SetVisibility(ESlateVisibility::Visible);

	UIManagerComponent = InUIManagerComponent;
	if (!UIManagerComponent) return;

	QuestTrackerWidget = Cast<UQuestTrackerWidget>(UIManagerComponent->GetWidget("Quest"));
	if (!QuestTrackerWidget) return;

	NotificationWidget = Cast<UNotificationWidget>(UIManagerComponent->GetWidget("Notification"));
	if (!NotificationWidget) return;

	if (SB_Quest && QuestTrackerWidget)
	{
		SB_Quest->SetContent(QuestTrackerWidget);
	}

	if (SB_Notification)
		SB_Notification->SetContent(NotificationWidget);
	
	SetBindingDelegates();
}

void UHUDWidget::SetBindingDelegates()
{
	APlayerController* PC = GetOwningPlayer();
	if (!PC) return;

	ACustomPlayerCharacter* Player = Cast<ACustomPlayerCharacter>(PC->GetPawn());
	if (!Player) return;

	// safe bind
	Player->OnNotificationVisibilityChanged.RemoveAll(this);

	Player->OnNotificationVisibilityChanged.AddDynamic(this, &UHUDWidget::ShowNotificationWidget);
}

void UHUDWidget::ShowNotificationWidget(bool bVisible)
{
	NotificationWidget->SetVisibility(bVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}
