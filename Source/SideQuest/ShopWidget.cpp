#include "ShopWidget.h"
#include "CustomPlayerCharacter.h"
#include "InventoryComponent.h"

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

		Entry->OnShopItemClicked.AddDynamic(this, &UShopWidget::HandleBuyItem);

		SB_Items->AddChild(Entry);
	}
}

void UShopWidget::HandleBuyItem(const FItemInstance& Item)
{
	if (!GetOwningPlayer()) return;

	ACustomPlayerCharacter* Player = Cast<ACustomPlayerCharacter>(GetOwningPlayer()->GetPawn());
	if (!Player) return;

	UInventoryComponent* InventoryComponent = Player->GetInventoryComponent();
	if (!InventoryComponent) return;

	InventoryComponent->AddItem(Item);

	UE_LOG(LogTemp, Warning, TEXT("Bought item: %s"), *UEnum::GetValueAsString(Item.WeaponType));
}