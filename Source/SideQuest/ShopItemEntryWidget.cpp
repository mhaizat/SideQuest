#include "ShopItemEntryWidget.h"

void UShopItemEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (BTN_Buy)
	{
		BTN_Buy->OnClicked.AddDynamic(this, &UShopItemEntryWidget::OnBuyClicked);
	}
}

void UShopItemEntryWidget::InitializeItem(const FItemInstance& InItem)
{
	ItemData = InItem;

	if (TXT_ItemName)
	{
		const UEnum* WeaponEnum = StaticEnum<EWeaponTypes>();

		FString ItemName = WeaponEnum ? WeaponEnum->GetDisplayNameTextByValue(static_cast<int64>(ItemData.WeaponType)).ToString() : TEXT("Unknown");

		TXT_ItemName->SetText(FText::FromString(ItemName));
	}

	AffixString.Empty();

	for (const FAffixInstance& Affix : ItemData.Affixes)
	{
		const UEnum* Enum = StaticEnum<EAffixType>();

		FString AffixName = Enum ? Enum->GetDisplayNameTextByValue(static_cast<int64>(Affix.Type)).ToString() : TEXT("Unknown");

		AffixString += FString::Printf(TEXT("%s +%.1f%%\n"), *AffixName, Affix.Value);
	}
}

void UShopItemEntryWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	OnItemHovered.Broadcast(ItemData);
}

void UShopItemEntryWidget::OnBuyClicked()
{
	OnShopItemClicked.Broadcast(ItemData);
}

void UShopItemEntryWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	OnItemUnhovered.Broadcast();
}
