#include "ItemTooltipWidget.h"

void UItemTooltipWidget::SetItem(const FItemInstance& Item)
{
	CurrentItem = Item;

	// NAME
	if (TXT_Name)
	{
		FString Name = UEnum::GetValueAsString(Item.WeaponType);
		FString Rarity = UEnum::GetValueAsString(Item.Rarity);

		TXT_Name->SetText(FText::FromString(Name + TEXT(" [") + Rarity + TEXT("]")));
	}

	// DAMAGE
	if (TXT_Damage)
	{
		FString Damage = FString::Printf(TEXT("Damage: %.0f"), Item.BaseDamage);
		TXT_Damage->SetText(FText::FromString(Damage));
	}

	// AFFIXES
	if (TXT_Affixes)
	{
		FString Text;

		for (const FAffixInstance& Affix : Item.Affixes)
		{
			const UEnum* Enum = StaticEnum<EAffixType>();
			FString AffixName = Enum
				? Enum->GetDisplayNameTextByValue((int64)Affix.Type).ToString()
				: TEXT("Unknown");

			Text += FString::Printf(TEXT("%s +%.1f%%\n"), *AffixName, Affix.Value);
		}

		TXT_Affixes->SetText(FText::FromString(Text));
	}
}

void UItemTooltipWidget::UpdatePosition(const FVector2D& ScreenPosition)
{
	if (!IsInViewport()) return;

	SetPositionInViewport(ScreenPosition, true);
}