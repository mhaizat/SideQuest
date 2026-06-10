#pragma once

#include "CoreMinimal.h"
#include "NPCBase.h"
#include "Components/SphereComponent.h"
#include "NPCInteractable.generated.h"

UCLASS()
class SIDEQUEST_API ANPCInteractable : public ANPCBase
{
	GENERATED_BODY()
	
public:
	ANPCInteractable();

	virtual void Interact(AActor* Interactor);

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* InteractionSphere;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	FText NPCName;

	UPROPERTY(EditAnywhere)
	FText DialogueText;

	UFUNCTION()
	void OnPlayerEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnPlayerExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
