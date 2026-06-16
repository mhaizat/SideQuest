#include "DialogueWidget.h"
#include "Components/TextBlock.h"
#include "UIManagerComponent.h"
#include "CustomPlayerCharacter.h"
#include "DialogueComponent.h"

void UDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDialogueWidget::InitializeWidget(UDialogueComponent* InDialogueComponent)
{
	if (!InDialogueComponent || bIsBound) return;


	CachedDialogue = InDialogueComponent;

	CachedDialogue->OnDialogueLine.RemoveAll(this);
	CachedDialogue->OnDialogueFinished.RemoveAll(this);
	CachedDialogue->OnDialogueChoiceRequested.RemoveAll(this);

	CachedDialogue->OnDialogueLine.AddDynamic(this, &UDialogueWidget::HandleDialogueLine);
	CachedDialogue->OnDialogueFinished.AddDynamic(this, &UDialogueWidget::HandleDialogueFinished);
	CachedDialogue->OnDialogueChoiceRequested.AddDynamic(this, &UDialogueWidget::HandleDialogueChoices);

	bIsBound = true;

	UE_LOG(LogTemp, Warning, TEXT("DialogueWidget bound once"));
}

void UDialogueWidget::HandleDialogueLine(FText Line)
{
	DialogueText->SetText(Line);
}

void UDialogueWidget::HandleDialogueFinished()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return;

	APawn* Pawn = PC->GetPawn();
	if (!Pawn) return;

	ACustomPlayerCharacter* Player = Cast<ACustomPlayerCharacter>(Pawn);
	if (!Player) return;

	UUIManagerComponent* UIManager = Player->GetUIManager();
	if (!UIManager) return;

	UIManager->HideWidget("Dialogue");

	UE_LOG(LogTemp, Warning, TEXT("Dialogue finished - hiding widget"));
}

void UDialogueWidget::HandleDialogueChoices(const TArray<FDialogueChoice>& Choices)
{
	ChoiceContainer->ClearChildren();

	if (Choices.Num() == 0)
	{
		ChoiceContainer->SetVisibility(ESlateVisibility::Collapsed);
		UE_LOG(LogTemp, Warning, TEXT("HandleDialogueChoices: No choice"));

		return;
	}

	ChoiceContainer->SetVisibility(ESlateVisibility::Visible);

	UE_LOG(LogTemp, Warning, TEXT("HandleDialogueChoices: Have choice"));

	for (int32 i = 0; i < Choices.Num(); i++)
	{
		const FDialogueChoice& Choice = Choices[i];

		UButtonChoiceWidget* Widget =
			CreateWidget<UButtonChoiceWidget>(GetWorld(), ButtonChoiceClass);

		Widget->Setup(Choice.Text, i, CachedDialogue);

		ChoiceContainer->AddChild(Widget);
	}
}
