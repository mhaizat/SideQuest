#pragma once

#include "CoreMinimal.h"
#include "SideQuestCharacter.h"
#include "AttributeComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "WeaponBase.h"
#include "WeaponManagerComponent.h"
#include "CustomPlayerCharacter.generated.h"

UCLASS()
class SIDEQUEST_API ACustomPlayerCharacter : public ASideQuestCharacter
{
	GENERATED_BODY()
	
public:
	ACustomPlayerCharacter();

	UFUNCTION()
	void AttackWindowStart();

	UFUNCTION()
	void AttackWindowEnd();

	void EquipWeaponSlot1();
	void EquipWeaponSlot2();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	void Attack();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAttributeComponent* Attributes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWeaponManagerComponent* WeaponManager;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* Slot1Action;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* Slot2Action;

	UPROPERTY()
	AWeaponBase* EquippedWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<AWeaponBase> WeaponClass;
};
