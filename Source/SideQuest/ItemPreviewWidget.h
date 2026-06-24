#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemPreviewWidget.generated.h"

UCLASS()
class SIDEQUEST_API UItemPreviewWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void ShowItem(const FItemInstance& Item);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TXT_Name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TXT_Rarity;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TXT_Damage;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TXT_Affixes;
};
