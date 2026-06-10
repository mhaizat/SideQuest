#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPCBase.generated.h"

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

public:	
	virtual void Tick(float DeltaTime) override;
};
