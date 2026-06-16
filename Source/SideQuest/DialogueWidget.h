#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ButtonChoiceWidget.h"
#include "DialogueData.h"
#include "DialogueWidget.generated.h"

class UDialogueComponent;

UCLASS()
class SIDEQUEST_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitializeWidget(UDialogueComponent* InDialogueComponent);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UButtonChoiceWidget> ButtonChoiceClass;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DialogueText;

	UPROPERTY()
	UDialogueComponent* CachedDialogue;

	UFUNCTION()
	void HandleDialogueLine(FText Line);

	UFUNCTION()
	void HandleDialogueFinished();

	bool bIsBound = false;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* ChoiceContainer;

	UFUNCTION()
	void HandleDialogueChoices(const TArray<FDialogueChoice>& Choices);
};
