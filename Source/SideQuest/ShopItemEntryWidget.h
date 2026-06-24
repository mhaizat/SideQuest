#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "ItemTypes.h"
#include "WeaponTypes.h"
#include "ShopItemEntryWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShopItemClicked, const FItemInstance&, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
    FOnItemHovered,
    const FItemInstance&,
    Item);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemUnhovered);

UCLASS()
class SIDEQUEST_API UShopItemEntryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    void InitializeItem(const FItemInstance& InItem);

    virtual void NativeOnMouseLeave(
        const FPointerEvent& InMouseEvent) override;

    FOnShopItemClicked OnShopItemClicked;

    UPROPERTY(BlueprintAssignable)
    FOnItemHovered OnItemHovered;
    UPROPERTY(BlueprintAssignable)
    FOnItemUnhovered OnItemUnhovered;

protected:
    virtual void NativeConstruct() override;

    virtual void NativeOnMouseEnter(
        const FGeometry& InGeometry,
        const FPointerEvent& InMouseEvent) override;

    UFUNCTION()
    void OnBuyClicked();

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TXT_ItemName;

    //UPROPERTY(meta = (BindWidget))
    //UTextBlock* TXT_Damage;

    //UPROPERTY(meta = (BindWidget))
    //UTextBlock* TXT_Affix;

    UPROPERTY(meta = (BindWidget))
    UButton* BTN_Buy;

    FString AffixString;

    FItemInstance ItemData;
};
