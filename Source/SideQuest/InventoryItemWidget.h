#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemTypes.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "InventoryItemWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnInventoryItemClicked,
	const FItemInstance&, Item);

UCLASS()
class SIDEQUEST_API UInventoryItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitializeItem(const FItemInstance& Item);

	UPROPERTY(BlueprintAssignable)
	FOnInventoryItemClicked OnInventoryItemClicked;

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TXT_ItemName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TXT_Damage;

	UPROPERTY(meta = (BindWidget))
	UButton* BTN_Equip;

	UPROPERTY()
	FItemInstance ItemData;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnEquipClicked();
};
