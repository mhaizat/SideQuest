#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponBase.h"
#include "WeaponManagerComponent.generated.h"

class ACharacter;
class ACustomPlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIDEQUEST_API UWeaponManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponManagerComponent();

	void EquipWeapon(int32 Index);
	void NextWeapon();

	void SetAttacking(bool bAttacking);

	bool IsAttacking() const;

	AWeaponBase* GetCurrentEquippedWeapon() { return EquippedWeapon; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	TArray<TSubclassOf<AWeaponBase>> WeaponInventory;

	UPROPERTY()
	AWeaponBase* EquippedWeapon;

	TArray<AWeaponBase*> SpawnedWeapons;

	int32 CurrentWeaponIndex = 0;

private:
	bool bIsAttacking = false;
};
