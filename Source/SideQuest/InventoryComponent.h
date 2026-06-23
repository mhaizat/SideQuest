#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemTypes.h"
#include "InventoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIDEQUEST_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	bool AddItem(const FItemInstance& Item);
	bool RemoveItem(int32 Index);

	//const TArray<FItemInstance>& GetItems() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Shop|Debug")
	TArray<FItemInstance> Items;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxSlots = 20;
};
