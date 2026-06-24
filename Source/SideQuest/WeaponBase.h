#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "DamageInterface.h"
#include "HitData.h"
#include "WeaponTypes.h"
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

	float GetDamage() const;
	void SetDamage(float Damage) { BaseDamage = Damage; }

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float BaseDamage = 20.f;

	UPROPERTY(EditDefaultsOnly)
	EWeaponTypes WeaponType;
};
