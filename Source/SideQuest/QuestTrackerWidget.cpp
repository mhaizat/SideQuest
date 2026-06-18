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

	CachedQuestManager->OnQuestUpdated.AddDynamic(this, &UQuestTrackerWidget::HandleQuestUpdated);

	UE_LOG(LogTemp, Warning, TEXT("QuestTracker NativeConstruct"));
	
}

void UQuestTrackerWidget::InitializeQuestDisplay(FQuestData QuestData)
{
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
		CachedQuestManager->OnQuestUpdated.RemoveAll(this);
	}

	Super::NativeDestruct();
}