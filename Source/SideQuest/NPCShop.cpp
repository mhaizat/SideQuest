#include "NPCShop.h"
#include "GameStateManagerComponent.h"

void ANPCShop::Interact(AActor* Interactor)
{
	Super::Interact(Interactor);

	ACustomPlayerCharacter* Player = Cast<ACustomPlayerCharacter>(Interactor);
	if (!Player) return;

	OpenShop(Player);
}

void ANPCShop::OpenShop(ACustomPlayerCharacter* Player)
{
	UGameStateManagerComponent* GameStateManagerComponent = Player->GetGameStateManagerComponent();
	if (!GameStateManagerComponent) return;

	UUIManagerComponent* UIManager = Player->GetUIManager();
	if (!UIManager) return;

	GameStateManagerComponent->SetState(EGameState::UIOnly);

	CurrentGeneratedItems.Empty();

	// TEMP: generate 3 items for now
	CurrentGeneratedItems.Add(GenerateItem(EWeaponTypes::Sword));
	CurrentGeneratedItems.Add(GenerateItem(EWeaponTypes::Axe));
	CurrentGeneratedItems.Add(GenerateItem(EWeaponTypes::Hammer));

	for (const FItemInstance& Item : CurrentGeneratedItems)
	{
		FString RarityString = UEnum::GetValueAsString(Item.Rarity);
		FString WeaponString = UEnum::GetValueAsString(Item.WeaponType);

		UE_LOG(LogTemp, Warning, TEXT("=== ITEM ==="));
		UE_LOG(LogTemp, Warning, TEXT("Weapon: %s"), *WeaponString);
		UE_LOG(LogTemp, Warning, TEXT("Rarity: %s"), *RarityString);
		UE_LOG(LogTemp, Warning, TEXT("BaseDamage: %f"), Item.BaseDamage);

		for (const FAffixInstance& Affix : Item.Affixes)
		{
			FString AffixType = UEnum::GetValueAsString(Affix.Type);

			UE_LOG(LogTemp, Warning, TEXT("  Affix: %s | Value: %f"), *AffixType, Affix.Value);
		}
	}



	UShopWidget* ShopWidget = Cast<UShopWidget>(UIManager->GetWidget("Shop"));
	if (!ShopWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("Shop widget not found"));
		return;
	}

	ShopWidget->SetShopItems(CurrentGeneratedItems);

	UIManager->ShowWidget("Shop");
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

	UE_LOG(LogTemp, Warning, TEXT("GenerateAffixes CALLED"));
	UE_LOG(LogTemp, Warning, TEXT("Rarity: %s"), *UEnum::GetValueAsString(Rarity));
	UE_LOG(LogTemp, Warning, TEXT("AffixPool Size: %d"), AffixPool.Num());
	UE_LOG(LogTemp, Warning, TEXT("AffixCount: %d"), AffixCount);

	// Safety check
	if (AffixPool.Num() == 0)
	{
		return Result;
	}

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