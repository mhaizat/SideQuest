#include "InventoryComponent.h"

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
