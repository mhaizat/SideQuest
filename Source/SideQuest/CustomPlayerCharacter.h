#pragma once

#include "CoreMinimal.h"
#include "SideQuestCharacter.h"
#include "AttributeComponent.h"
#include "CustomPlayerCharacter.generated.h"

UCLASS()
class SIDEQUEST_API ACustomPlayerCharacter : public ASideQuestCharacter
{
	GENERATED_BODY()
	
public:
	ACustomPlayerCharacter();


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAttributeComponent* Attributes;

	virtual void BeginPlay() override;
};
