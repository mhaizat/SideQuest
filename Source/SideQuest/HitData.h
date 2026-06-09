#pragma once

#include "CoreMinimal.h"
#include "HitData.generated.h"

class AActor;
class AWeaponBase;

USTRUCT(BlueprintType)
struct FHitData
{
	GENERATED_BODY()

	// How much damage this hit deals
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 0.f;

	// Direction the attack came from (used for hit reaction logic)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector AttackDirection = FVector::ZeroVector;

	// Who caused the hit (player or AI)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* InstigatorActor = nullptr;

	// Which weapon caused the hit (sword, axe, etc.)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AWeaponBase* Weapon = nullptr;
};