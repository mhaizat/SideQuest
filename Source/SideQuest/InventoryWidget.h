#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemTypes.h"
#include "InventoryItemWidget.h"
#include "InventoryWidget.generated.h"

class UScrollBox;
class UInventoryComponent;

UCLASS()
class SIDEQUEST_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetInventory(UInventoryComponent* InInventory);

protected:

	UPROPERTY(meta = (BindWidget))
	UScrollBox* SB_Items;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryItemWidget> ItemEntryClass;

	UFUNCTION()
	void HandleEquipItem(const FItemInstance& Item);

private:

	UPROPERTY()
	UInventoryComponent* InventoryRef;

	void RefreshUI();

};
