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
		Entry->OnItemHovered.AddDynamic(this, &UShopWidget::HandleItemHovered);

		Entry->OnItemUnhovered.AddDynamic(
			this,
			&UShopWidget::HandleItemUnhovered);

		SB_Items->AddChild(Entry);

		ItemPreviewWidget->SetVisibility(ESlateVisibility::Collapsed);
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

void UShopWidget::HandleItemHovered(const FItemInstance& Item)
{
	if (!ItemPreviewWidget) return;

	ItemPreviewWidget->ShowItem(Item);
	ItemPreviewWidget->SetVisibility(ESlateVisibility::Visible);
}

void UShopWidget::HandleItemUnhovered()
{
	if (!ItemPreviewWidget) return;

	ItemPreviewWidget->SetVisibility(ESlateVisibility::Collapsed);
}