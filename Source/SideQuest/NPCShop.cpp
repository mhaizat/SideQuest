#include "NPCShop.h"

void ANPCShop::Interact(AActor* Interactor)
{
	Super::Interact(Interactor);

	ACustomPlayerCharacter* Player = Cast<ACustomPlayerCharacter>(Interactor);
	if (!Player) return;

	OpenShop(Player);
}

void ANPCShop::OpenShop(ACustomPlayerCharacter* Player)
{
	UUIManagerComponent* UI = Player->GetUIManager();
	if (!UI) return;

	UUserWidget* Widget = UI->GetWidget("Shop");
	if (!Widget)
	{
		UE_LOG(LogTemp, Warning, TEXT("Shop widget not found"));
		return;
	}

	UI->ShowWidget("Shop");

	UE_LOG(LogTemp, Warning, TEXT("Shop opened"));
}

void ANPCShop::AddItem(const FShopItem& Item)
{
	ShopItems.Add(Item);

	UE_LOG(LogTemp, Warning, TEXT("Item added: %s"), *Item.ItemID.ToString());
}

void ANPCShop::RemoveItem(FName ItemID)
{
	ShopItems.RemoveAll([&](const FShopItem& Item)
		{
			return Item.ItemID == ItemID;
		});

	UE_LOG(LogTemp, Warning, TEXT("Item removed: %s"), *ItemID.ToString());
}

TArray<FShopItem>& ANPCShop::GetShopItems()
{
	return ShopItems;
}