#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

UCLASS()
class SIDEQUEST_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitializeWidget(UDialogueComponent* InDialogueComponent);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DialogueText;

	UPROPERTY()
	UDialogueComponent* CachedDialogue;

	UFUNCTION()
	void HandleDialogueLine(FText Line);

	UFUNCTION()
	void HandleDialogueFinished();
};
