#pragma once

#include "CoreMinimal.h"
#include "WeaponTypes.h"
#include "HitData.generated.h"

class AActor;
class AWeaponBase;

USTRUCT(BlueprintType)
struct FHitData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector AttackDirection = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* InstigatorActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AWeaponBase* Weapon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponTypes WeaponType;
};