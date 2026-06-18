#include "HUDWidget.h"

void UHUDWidget::InitializeHUDWidget(UUIManagerComponent* InUIManagerComponent)
{
	UE_LOG(LogTemp, Warning, TEXT("InitializeHUDWidget 1"));

	SetVisibility(ESlateVisibility::Visible);

	UIManagerComponent = InUIManagerComponent;
	if (!UIManagerComponent) return;
		
	UE_LOG(LogTemp, Warning, TEXT("InitializeHUDWidget 2"));

	UUserWidget* Widget = UIManagerComponent->GetWidget("Quest");
	if (!Widget)
	{
		UE_LOG(LogTemp, Warning, TEXT("InitializeHUDWidget 3"));
		return;
	}

	QuestTrackerWidget = Cast<UQuestTrackerWidget>(Widget);
	if (!QuestTrackerWidget) return;

	//QuestTrackerWidget->SetVisibility(ESlateVisibility::Visible);

	UE_LOG(LogTemp, Warning, TEXT("InitializeHUDWidget 4"));

	if (SB_Quest && QuestTrackerWidget)
	{
		SB_Quest->SetContent(QuestTrackerWidget);
	}
}
