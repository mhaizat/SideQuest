#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestItem.generated.h"

UCLASS()
class SIDEQUEST_API AQuestItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AQuestItem();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
		
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* CollisionSphere;

	//! Used by quests
	UPROPERTY(EditAnywhere, Category = "Quest")
	FName ItemID = "Herb";
};
