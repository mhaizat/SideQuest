#include "NPCShop.h"
#include "GameStateManagerComponent.h"

void ANPCShop::Interact(AActor* Interactor)
{
	Super::Interact(Interactor);

	ACustomPlayerCharacter* Player = Cast<ACustomPlayerCharacter>(Interactor);
	if (!Player) return;

	if (IsOpen)
	{
		CloseShop(Player);
	}
	else
	{
		OpenShop(Player);
	}
}

void ANPCShop::OpenShop(ACustomPlayerCharacter* Player)
{
	UGameStateManagerComponent* GameStateManagerComponent = Player->GetGameStateManagerComponent();
	if (!GameStateManagerComponent) return;

	UUIManagerComponent* UIManager = Player->GetUIManager();
	if (!UIManager) return;

	GameStateManagerComponent->SetState(EGameState::UIOnly);

	CurrentGeneratedItems.Empty();

	CurrentGeneratedItems.Add(GenerateItem(EWeaponTypes::Sword));
	CurrentGeneratedItems.Add(GenerateItem(EWeaponTypes::Axe));
	CurrentGeneratedItems.Add(GenerateItem(EWeaponTypes::Hammer));

	UShopWidget* ShopWidget = Cast<UShopWidget>(UIManager->GetWidget("Shop"));
	if (!ShopWidget) return;

	ShopWidget->SetShopItems(CurrentGeneratedItems);

	UIManager->ShowWidget("Shop");

	IsOpen = true;

	UE_LOG(LogTemp, Warning, TEXT("Shop Opened"));
}

void ANPCShop::CloseShop(ACustomPlayerCharacter* Player)
{
	UUIManagerComponent* UIManager = Player->GetUIManager();
	if (!UIManager) return;

	UGameStateManagerComponent* GameStateManagerComponent = Player->GetGameStateManagerComponent();
	if (!GameStateManagerComponent) return;

	GameStateManagerComponent->SetState(EGameState::Gameplay);

	UIManager->HideWidget("Shop"); // or remove / collapse depending on your system

	IsOpen = false;

	UE_LOG(LogTemp, Warning, TEXT("Shop Closed"));
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

FItemInstance ANPCShop::GenerateItem(EWeaponTypes WeaponType)
{
	FItemInstance Item;

	Item.WeaponType = WeaponType;
	Item.Rarity = RollRarity();

	switch (Item.Rarity)
	{
	case EItemRarity::Basic:
		Item.BaseDamage = 20.f;
		break;
	case EItemRarity::Rare:
		Item.BaseDamage = 25.f;
		break;
	case EItemRarity::Epic:
		Item.BaseDamage = 32.f;
		break;
	case EItemRarity::Legendary:
		Item.BaseDamage = 40.f;
		break;
	}

	Item.Affixes = GenerateAffixes(Item.Rarity);

	return Item;
}

TArray<FAffixInstance> ANPCShop::GenerateAffixes(EItemRarity Rarity)
{
	TArray<FAffixInstance> Result;

	int32 AffixCount = 0;

	switch (Rarity)
	{
	case EItemRarity::Basic:
		AffixCount = FMath::RandRange(0, 1);
		break;

	case EItemRarity::Rare:
		AffixCount = FMath::RandRange(1, 2);
		break;

	case EItemRarity::Epic:
		AffixCount = FMath::RandRange(2, 3);
		break;

	case EItemRarity::Legendary:
		AffixCount = FMath::RandRange(3, 4);
		break;
	}

	if (AffixPool.Num() == 0) return Result;

	for (int32 i = 0; i < AffixCount; i++)
	{
		int32 Index = FMath::RandRange(0, AffixPool.Num() - 1);
		const FAffixDefinition& Def = AffixPool[Index];

		FAffixInstance Instance;
		Instance.Type = Def.Type;
		Instance.Value = FMath::FRandRange(Def.MinValue, Def.MaxValue);

		Result.Add(Instance);;
	}

	return Result;
}

EItemRarity ANPCShop::RollRarity()
{
	int32 Roll = FMath::RandRange(1, 100);

	if (Roll <= 50) return EItemRarity::Basic;
	if (Roll <= 75) return EItemRarity::Rare;
	if (Roll <= 90) return EItemRarity::Epic;
	return EItemRarity::Legendary;
}