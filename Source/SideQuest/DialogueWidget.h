#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "DialogueWidget.generated.h"

UCLASS()
class SIDEQUEST_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitializeWidget(UDialogueComponent* InDialogueComponent);

protected:
	virtual void NativeConstruct() override;

	//UFUNCTION()
	//void OnChoiceClicked();

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* ChoiceBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DialogueText;

	UPROPERTY()
	UDialogueComponent* CachedDialogue;

	UFUNCTION()
	void HandleDialogueLine(FText Line);

	UFUNCTION()
	void HandleDialogueFinished();

	bool bIsBound = false;

	/*UFUNCTION()
	void HandleDialogueChoices(const TArray<FDialogueChoice>& Choices);*/
};
