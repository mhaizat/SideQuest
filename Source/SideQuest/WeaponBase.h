#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "DamageInterface.h"
#include "HitData.h"
#include "WeaponBase.generated.h"

UCLASS()
class SIDEQUEST_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponBase();

	bool IsTracable() { return bCanTrace; }

	void StartTrace();
	void StopTrace();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	void PerformTrace();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY()
	bool bCanTrace = false;

	TArray<AActor*> HitActors;
};
