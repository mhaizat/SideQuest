#include "InventoryComponent.h"
#include "Components/ScrollBox.h"
#include "GameStateManagerComponent.h"
#include "CustomPlayerCharacter.h"

void UInventoryWidget::SetInventory(UInventoryComponent* InInventory)
{
	APlayerController* PC = GetOwningPlayer();
	if (!PC) return;

	ACustomPlayerCharacter* Player =
		Cast<ACustomPlayerCharacter>(PC->GetPawn());

	UGameStateManagerComponent* GameStateManagerComponent = Cast<UGameStateManagerComponent>(Player->GetGameStateManagerComponent());
	if (!GameStateManagerComponent) return;

	GameStateManagerComponent->SetState(EGameState::UIOnly);

	InventoryRef = InInventory;
	RefreshUI();
}

void UInventoryWidget::RefreshUI()
{
	if (!SB_Items || !InventoryRef) return;

	UE_LOG(LogTemp, Warning, TEXT("RefreshUI"));

	SB_Items->ClearChildren();

	const TArray<FItemInstance>& Items = InventoryRef->GetItems();

	for (int32 i = 0; i < Items.Num(); i++)
	{
		UInventoryItemWidget* Entry = CreateWidget<UInventoryItemWidget>(GetWorld(), ItemEntryClass);
		if (!Entry) continue;

		Entry->InitializeItem(Items[i]);

		// CLICK → EQUIP
		int32 Index = i;

		Entry->OnInventoryItemClicked.AddDynamic(
			this,
			&UInventoryWidget::HandleEquipItem);

		SB_Items->AddChild(Entry);
	}
}

void UInventoryWidget::HandleEquipItem(const FItemInstance& Item)
{
	APlayerController* PC = GetOwningPlayer();
	if (!PC) return;

	ACustomPlayerCharacter* Player =
		Cast<ACustomPlayerCharacter>(PC->GetPawn());

	if (!Player) return;

	Player->GetInventoryComponent()->EquipItem(Item);
}

