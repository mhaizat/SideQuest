#include "QuestTrackerWidget.h"
#include "Components/TextBlock.h"
#include "CustomPlayerCharacter.h"
#include "QuestManagerComponent.h"

void UQuestTrackerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return;

	APawn* Pawn = PC->GetPawn();
	if (!Pawn) return;

	ACustomPlayerCharacter* Player = Cast<ACustomPlayerCharacter>(Pawn);
	if (!Player) return;

	CachedQuestManager = Player->GetQuestManager();
	if (!CachedQuestManager) return;

	CachedQuestManager->OnQuestStarted.AddDynamic(this, &UQuestTrackerWidget::InitializeQuestDisplay);
	CachedQuestManager->OnQuestUpdated.AddDynamic(this, &UQuestTrackerWidget::HandleQuestUpdated);
	CachedQuestManager->OnQuestCompleted.AddDynamic(this, &UQuestTrackerWidget::HandleQuestCompleted);

	UE_LOG(LogTemp, Warning, TEXT("QuestTracker NativeConstruct"));
}

void UQuestTrackerWidget::InitializeQuestDisplay(FQuestData QuestData)
{
	SetVisibility(ESlateVisibility::Visible);

	if (QuestNameText)
	{
		QuestNameText->SetText(QuestData.QuestName);
	}

	if (ProgressText)
	{
		FString Text = FString::Printf(TEXT("%d / %d"), QuestData.CurrentAmount, QuestData.RequiredAmount);
		ProgressText->SetText(FText::FromString(Text));
	}
}

void UQuestTrackerWidget::HandleQuestCompleted(FQuestData Quest)
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UQuestTrackerWidget::HandleQuestUpdated(FQuestData Quest)
{
	if (QuestNameText)
	{
		QuestNameText->SetText(Quest.QuestName);
	}

	if (ProgressText)
	{
		FString Text = FString::Printf(TEXT("%d / %d"), Quest.CurrentAmount, Quest.RequiredAmount);
		ProgressText->SetText(FText::FromString(Text));
	}
}

void UQuestTrackerWidget::NativeDestruct()
{
	if (CachedQuestManager)
	{
		CachedQuestManager->OnQuestStarted.RemoveAll(this);
		CachedQuestManager->OnQuestUpdated.RemoveAll(this);
		CachedQuestManager->OnQuestCompleted.RemoveAll(this);
	}

	Super::NativeDestruct();
}