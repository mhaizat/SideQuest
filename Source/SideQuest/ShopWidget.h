#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemTypes.h"
#include "ShopWidget.generated.h"

UCLASS()
class SIDEQUEST_API UShopWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetShopItems(const TArray<FItemInstance>& Items);

protected:
	UPROPERTY(VisibleAnywhere)
	TArray<FItemInstance> ShopItems;
	
};
