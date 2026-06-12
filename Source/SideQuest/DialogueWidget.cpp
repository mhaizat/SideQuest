#include "DialogueWidget.h"
#include "Components/TextBlock.h"
#include "UIManagerComponent.h"
#include "CustomPlayerCharacter.h"
#include "DialogueComponent.h"

void UDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return;

	ACustomPlayerCharacter* Player = Cast<ACustomPlayerCharacter>(PC->GetPawn());
	if (!Player) return;

	CachedDialogue = Player->GetDialogueComponent();
	if (!CachedDialogue) return;

	// IMPORTANT: prevent duplicate binding
	CachedDialogue->OnDialogueLine.RemoveAll(this);
	CachedDialogue->OnDialogueFinished.RemoveAll(this);

	CachedDialogue->OnDialogueLine.AddDynamic(this, &UDialogueWidget::HandleDialogueLine);
	CachedDialogue->OnDialogueFinished.AddDynamic(this, &UDialogueWidget::HandleDialogueFinished);

	UE_LOG(LogTemp, Warning, TEXT("DialogueWidget bound once"));
}

void UDialogueWidget::InitializeWidget(UDialogueComponent* InDialogueComponent)
{
	CachedDialogue = InDialogueComponent;

	if (!CachedDialogue) return;

	CachedDialogue->OnDialogueLine.AddDynamic(this, &UDialogueWidget::HandleDialogueLine);
	CachedDialogue->OnDialogueFinished.AddDynamic(this, &UDialogueWidget::HandleDialogueFinished);

	UE_LOG(LogTemp, Warning, TEXT("Bound to DialogueComponent"));
}

void UDialogueWidget::HandleDialogueLine(FText Line)
{
	UE_LOG(LogTemp, Warning, TEXT("Widget received line"));

	if (DialogueText)
	{
		DialogueText->SetText(Line);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DialogueText is NULL"));
	}
}

void UDialogueWidget::HandleDialogueFinished()
{
	RemoveFromParent();

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return;

	APawn* Pawn = PC->GetPawn();
	if (!Pawn) return;

	ACustomPlayerCharacter* Player = Cast<ACustomPlayerCharacter>(Pawn);
	if (!Player) return;

	UUIManagerComponent* UIManager = Player->GetUIManager();
	if (!UIManager) return;

	UIManager->HideWidget("Dialogue");
}