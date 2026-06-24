#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponBase.h"
#include "ItemTypes.h"
#include "WeaponManagerComponent.generated.h"

class ACharacter;
class ACustomPlayerCharacter;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIDEQUEST_API UWeaponManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeaponManagerComponent();

	void EquipItem(const FItemInstance& Item);

	void SetAttacking(bool bAttacking);
	bool IsAttacking() const;

	AWeaponBase* GetCurrentEquippedWeapon() { return EquippedWeapon; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	FItemInstance EquippedItem;

	UPROPERTY()
	AWeaponBase* EquippedWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	TSubclassOf<AWeaponBase> SwordClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	TSubclassOf<AWeaponBase> AxeClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	TSubclassOf<AWeaponBase> HammerClass;

private:
	bool bIsAttacking = false;
};
