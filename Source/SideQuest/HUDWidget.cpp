#include "HUDWidget.h"
#include "CustomPlayerCharacter.h"
#include "QuestManagerComponent.h"
#include "GameFramework/Actor.h"

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PC = GetOwningPlayer();

	ACustomPlayerCharacter* Player = Cast<ACustomPlayerCharacter>(PC->GetPawn());
	if (!Player) return;

	QuestManagerComponent = Player->GetQuestManager();
}

void UHUDWidget::NativeDestruct()
{
}

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

	SetBindingDelegates();
}

void UHUDWidget::SetBindingDelegates()
{
	UE_LOG(LogTemp, Warning, TEXT("SetBindingDelegates 1"));

	UUserWidget* Widget = UIManagerComponent->GetWidget("Notification");
	NotificationWidget = Cast<UNotificationWidget>(Widget);
	if (!NotificationWidget) return;

	UE_LOG(LogTemp, Warning, TEXT("SetBindingDelegates 2"));


	SB_Notification->SetContent(NotificationWidget);

	APlayerController* PC = GetOwningPlayer();
	if (!PC) return;

	UE_LOG(LogTemp, Warning, TEXT("SetBindingDelegates 3"));

	ACustomPlayerCharacter* Player = Cast<ACustomPlayerCharacter>(PC->GetPawn());
	if (!Player) return;

	UE_LOG(LogTemp, Warning, TEXT("SetBindingDelegates 4"));

	// safe bind
	Player->OnNotificationVisibilityChanged.RemoveAll(this);

	Player->OnNotificationVisibilityChanged.AddDynamic(this, &UHUDWidget::ShowNotificationWidget);
}

void UHUDWidget::ShowNotificationWidget(bool bVisible)
{
	NotificationWidget->SetVisibility(bVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}
