#pragma once

#include "CoreMinimal.h"
#include "NPCInteractable.h"
#include "QuestData.h"
#include "DialogueDataAsset.h"
#include "NPCQuestGiver.generated.h"

UCLASS()
class SIDEQUEST_API ANPCQuestGiver : public ANPCInteractable
{
	GENERATED_BODY()

public:
	virtual void Interact(AActor* Interactor) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	bool bQuestGiven = false;

	UPROPERTY(EditAnywhere, Category = "Quest")
	FQuestData QuestData;

	UPROPERTY(EditAnywhere, Category = "Dialogue")
	UDialogueDataAsset* DialogueAsset;

	virtual void OnPlayerEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnPlayerExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};