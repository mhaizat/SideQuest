#include "InventoryItemWidget.h"

void UInventoryItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (BTN_Equip)
	{
		BTN_Equip->OnClicked.AddDynamic(
			this,
			&UInventoryItemWidget::OnEquipClicked);
	}
}

void UInventoryItemWidget::InitializeItem(
	const FItemInstance& Item)
{
	ItemData = Item;

	if (TXT_ItemName)
	{
		TXT_ItemName->SetText(
			FText::FromString(
				UEnum::GetDisplayValueAsText(Item.WeaponType).ToString()));
	}

	if (TXT_Damage)
	{
		FString DamageText =
			FString::Printf(TEXT("Damage: %.0f"), Item.BaseDamage);

		TXT_Damage->SetText(
			FText::FromString(DamageText));
	}
}

void UInventoryItemWidget::OnEquipClicked()
{
	OnInventoryItemClicked.Broadcast(ItemData);
}