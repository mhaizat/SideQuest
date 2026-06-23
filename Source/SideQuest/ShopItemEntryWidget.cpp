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
	Item = InItem;

	if (TXT_ItemName)
	{
		FString ItemName = UEnum::GetValueAsString(Item.WeaponType);

		TXT_ItemName->SetText(FText::FromString(ItemName));
	}

	if (TXT_Damage)
	{
		FString DamageText = FString::Printf(TEXT("Damage: %.0f"), Item.BaseDamage);

		TXT_Damage->SetText(FText::FromString(DamageText));
	}

	AffixString.Empty();

	for (const FAffixInstance& Affix : Item.Affixes)
	{
		const UEnum* Enum = StaticEnum<EAffixType>();

		FString AffixName = Enum ? Enum->GetDisplayNameTextByValue(static_cast<int64>(Affix.Type)).ToString() : TEXT("Unknown");

		AffixString += FString::Printf(TEXT("%s +%.1f%%\n"), *AffixName, Affix.Value);
	}

	if (TXT_Affix)
	{
		TXT_Affix->SetText(FText::FromString(AffixString));
	}
}

void UShopItemEntryWidget::OnBuyClicked()
{
	OnShopItemClicked.Broadcast(Item);
}
