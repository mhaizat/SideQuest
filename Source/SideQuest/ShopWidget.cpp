#include "ShopWidget.h"

void UShopWidget::SetShopItems(const TArray<FItemInstance>& Items)
{
	ShopItems = Items;

	UE_LOG(LogTemp, Warning, TEXT("Shop received %d items"), Items.Num());

	for (const FItemInstance& Item : ShopItems)
	{
		if (!ShopItemEntryClass) continue;

		UShopItemEntryWidget* Entry = CreateWidget<UShopItemEntryWidget>(GetWorld(), ShopItemEntryClass);
		if (!Entry) continue;

		Entry->InitializeItem(Item);

		SB_Items->AddChild(Entry);
	}
}
