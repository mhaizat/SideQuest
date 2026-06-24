#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemTypes.h"
#include "Components/TextBlock.h"
#include "ItemTooltipWidget.generated.h"

UCLASS()
class SIDEQUEST_API UItemTooltipWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	// Called when hovering an item
	void SetItem(const FItemInstance& Item);

	// Cursor follow update
	void UpdatePosition(const FVector2D& ScreenPosition);

protected:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TXT_Name;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TXT_Damage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TXT_Affixes;

private:
	FItemInstance CurrentItem;

};
