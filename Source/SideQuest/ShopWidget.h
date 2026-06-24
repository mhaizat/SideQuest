#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemTypes.h"
#include "Components/ScrollBox.h"
#include "ShopItemEntryWidget.h"
#include "ItemPreviewWidget.h"
#include "ShopWidget.generated.h"

UCLASS()
class SIDEQUEST_API UShopWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetShopItems(const TArray<FItemInstance>& Items);

protected:
	UFUNCTION()
	void HandleBuyItem(const FItemInstance& Item);
	UFUNCTION()
	void HandleItemHovered(const FItemInstance& Item);
	UFUNCTION()
	void HandleItemUnhovered();

	UPROPERTY(VisibleAnywhere)
	TArray<FItemInstance> ShopItems;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* SB_Items;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UShopItemEntryWidget> ShopItemEntryClass;

	UPROPERTY(meta = (BindWidget))
	UItemPreviewWidget* ItemPreviewWidget;
};
