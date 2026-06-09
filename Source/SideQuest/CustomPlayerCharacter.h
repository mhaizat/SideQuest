#pragma once

#include "CoreMinimal.h"
#include "SideQuestCharacter.h"
#include "AttributeComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "WeaponBase.h"
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

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	void Attack();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAttributeComponent* Attributes;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	UPROPERTY()
	AWeaponBase* EquippedWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<AWeaponBase> WeaponClass;
};
