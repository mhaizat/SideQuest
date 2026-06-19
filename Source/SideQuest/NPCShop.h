#pragma once

#include "CoreMinimal.h"
#include "NPCInteractable.h"
#include "NPCShop.generated.h"

USTRUCT(BlueprintType)
struct FShopItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Price = 0;
};

UCLASS()
class SIDEQUEST_API ANPCShop : public ANPCInteractable
{
	GENERATED_BODY()
	
public:
	virtual void Interact(AActor* Interactor) override;

	// barebone shop manipulation
	void AddItem(const FShopItem& Item);
	void RemoveItem(FName ItemID);

	TArray<FShopItem>& GetShopItems();

protected:
	UPROPERTY(EditAnywhere, Category = "Shop")
	TArray<FShopItem> ShopItems;

	void OpenShop(class ACustomPlayerCharacter* Player);
};
