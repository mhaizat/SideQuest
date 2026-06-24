#include "ItemPreviewWidget.h"

void UItemPreviewWidget::ShowItem(const FItemInstance& Item)
{
	if (TXT_Name)
	{
		const UEnum* Enum = StaticEnum<EWeaponTypes>();
		FString Name = Enum ? Enum->GetDisplayNameTextByValue(static_cast<int64>(Item.WeaponType)).ToString() : TEXT("Unknown");

		TXT_Name->SetText(FText::FromString(Name));
	}

	if (TXT_Rarity)
	{
		const UEnum* Enum = StaticEnum<EItemRarity>();
		FString Rarity = Enum ? Enum->GetDisplayNameTextByValue(static_cast<int64>(Item.Rarity)).ToString() : TEXT("Unknown");

		TXT_Rarity->SetText(FText::FromString(Rarity));
	}

	if (TXT_Damage)
	{
		TXT_Damage->SetText(FText::FromString(FString::Printf(TEXT("Damage: %.0f"), Item.BaseDamage)));
	}

	if (TXT_Affixes)
	{
		FString AffixText;

		for (const FAffixInstance& Affix : Item.Affixes)
		{
			const UEnum* Enum = StaticEnum<EAffixType>();
			FString AffixName = Enum ? Enum->GetDisplayNameTextByValue(static_cast<int64>(Affix.Type)).ToString() : TEXT("Unknown");

			AffixText += FString::Printf(TEXT("%s +%.1f%%\n"), *AffixName, Affix.Value);
		}

		TXT_Affixes->SetText(FText::FromString(AffixText));
	}
}