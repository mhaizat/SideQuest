#include "ButtonChoiceWidget.h"
#include "DialogueComponent.h"

void UButtonChoiceWidget::Setup(const FText& InText, int32 InChoiceIndex, UDialogueComponent* InDialogue)
{
	ChoiceText->SetText(InText);

	ChoiceIndex = InChoiceIndex;
	DialogueRef = InDialogue;

	ChoiceButton->OnClicked.RemoveAll(this);
	ChoiceButton->OnClicked.AddDynamic(this, &UButtonChoiceWidget::OnClicked);
}

void UButtonChoiceWidget::OnClicked()
{
	if (!DialogueRef.IsValid()) return;

	DialogueRef->SelectChoice(ChoiceIndex);
}