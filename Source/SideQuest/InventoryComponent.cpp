#include "InventoryComponent.h"
#include "WeaponManagerComponent.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UInventoryComponent::AddItem(const FItemInstance& Item)
{
    if (Items.Num() >= MaxSlots) return false;
       
    Items.Add(Item);

    UE_LOG(LogTemp, Warning, TEXT("Inventory Item Added"));

    return true;
}

bool UInventoryComponent::EquipItem(const FItemInstance& Item)
{
    EquippedItems.Weapon = Item;

    ACustomPlayerCharacter* Player = Cast<ACustomPlayerCharacter>(GetOwner());
    if (!Player) return false;

    if (UWeaponManagerComponent* WeaponManager = Player->GetWeaponManagerComponent())
    {
        WeaponManager->EquipItem(Item);
    }

    return true;
}


bool UInventoryComponent::RemoveItem(int32 Index)
{
	if (!Items.IsValidIndex(Index))
		return false;

	Items.RemoveAt(Index);
	return true;
}

const TArray<FItemInstance>& UInventoryComponent::GetItems() const
{
    return Items;
}
