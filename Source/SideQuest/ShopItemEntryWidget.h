#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "ItemTypes.h"
#include "ShopItemEntryWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
    FOnShopItemClicked,
    const FItemInstance&, Item);

UCLASS()
class SIDEQUEST_API UShopItemEntryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    void InitializeItem(const FItemInstance& Item);

    FOnShopItemClicked OnShopItemClicked;

protected:

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TXT_ItemName;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TXT_Damage;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TXT_Affix;

    UPROPERTY(meta = (BindWidget))
    UButton* BTN_Buy;

    FString AffixString;
};
