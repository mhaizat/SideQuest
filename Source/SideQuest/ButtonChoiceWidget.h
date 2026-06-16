#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonChoiceWidget.generated.h"

class UDialogueComponent;

UCLASS()
class SIDEQUEST_API UButtonChoiceWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Setup(const FText& InText, int32 InChoiceIndex, UDialogueComponent* InDialogue);

protected:

	UPROPERTY(meta = (BindWidget))
	class UButton* ChoiceButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ChoiceText;

private:
	int32 ChoiceIndex;

	TWeakObjectPtr<UDialogueComponent> DialogueRef;

	UFUNCTION()
	void OnClicked();
};
