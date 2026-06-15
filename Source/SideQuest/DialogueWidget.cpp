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

	CachedDialogue->OnDialogueLine.AddDynamic(this, &UDialogueWidget::HandleDialogueLine);
	CachedDialogue->OnDialogueFinished.AddDynamic(this, &UDialogueWidget::HandleDialogueFinished);

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

	//SetVisibility(ESlateVisibility::Collapsed);
	UIManager->HideWidget("Dialogue");

	UE_LOG(LogTemp, Warning, TEXT("Dialogue finished - hiding widget"));
}

//void UDialogueWidget::HandleDialogueChoices(const TArray<FDialogueChoice>& Choices)
//{
	//if (!ChoiceBox) return;

	//ChoiceBox->ClearChildren();

	//for (int32 i = 0; i < Choices.Num(); i++)
	//{
	//	const FDialogueChoice& Choice = Choices[i];

	//	UButton* Button = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass());

	//	UTextBlock* Text = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	//	Text->SetText(Choice.Text);

	//	Button->AddChild(Text);

	//	// capture index safely via user index
	//	const int32 Index = i;

	//	Button->OnClicked.AddDynamic(this, &UDialogueWidget::OnChoiceClicked);
	//	Button->SetUserFocus(this);

	//	Button->SetTag(FName(*FString::FromInt(Index)));

	//	ChoiceBox->AddChild(Button);
	//}
//}

//void UDialogueWidget::OnChoiceClicked()
//{
	//UButton* Button = Cast<UButton>(GetFocusedWidget());
	//if (!Button || !CachedDialogue) return;

	//int32 Index = FCString::Atoi(*Button->GetTag().ToString());

	//CachedDialogue->SelectChoice(Index);

	//ChoiceBox->ClearChildren();
//}