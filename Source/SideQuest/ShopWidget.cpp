#include "ShopWidget.h"

void UShopWidget::SetShopItems(const TArray<FItemInstance>& Items)
{
	ShopItems = Items;

	UE_LOG(LogTemp, Warning, TEXT("Shop received %d items"), Items.Num());

	for (const FItemInstance& Item : ShopItems)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item: %s"),
			*UEnum::GetValueAsString(Item.WeaponType));
	}
}
