#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPCBase.generated.h"

UENUM(BlueprintType)
enum class ENPCType : uint8
{
	Dialogue,
	QuestGiver,
	Shop
};

UCLASS()
class SIDEQUEST_API ANPCBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ANPCBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "NPC")
	ENPCType NPCType;

public:	
	virtual void Tick(float DeltaTime) override;
};
