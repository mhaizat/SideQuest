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
	USphereComponent* InteractionSphere;

	virtual void HandleDialogue(AActor* Interactor);
	virtual void HandleQuest(AActor* Interactor);
	virtual void HandleShop(AActor* Interactor);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	FText NPCName;

	UPROPERTY(EditAnywhere)
	FText DialogueText;

	// Delegate handlers (bound to overlap events)
	UFUNCTION()
	void HandlePlayerEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void HandlePlayerExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Override these in child classes
	virtual void OnPlayerEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void OnPlayerExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};