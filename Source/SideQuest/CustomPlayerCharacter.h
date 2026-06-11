#pragma once

#include "CoreMinimal.h"
#include "SideQuestCharacter.h"
#include "AttributeComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "WeaponBase.h"
#include "WeaponManagerComponent.h"
#include "Components/SphereComponent.h"
#include "NPCInteractable.h"
#include "QuestManagerComponent.h"
#include "UIManagerComponent.h"
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
	UFUNCTION()
	void AttackFinished();

	void EquipWeaponSlot1();
	void EquipWeaponSlot2();

	void SetCurrentNPC(ANPCInteractable* NPC);
	void ClearCurrentNPC(ANPCInteractable* NPC);

	UQuestManagerComponent* GetQuestManager() const { return QuestManager; }
	UUIManagerComponent* GetUIManager() const { return UIManager; };

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	void Attack();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAttributeComponent* Attributes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWeaponManagerComponent* WeaponManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UQuestManagerComponent* QuestManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UUIManagerComponent* UIManager;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* InteractAction;

	UPROPERTY()
	AWeaponBase* EquippedWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<AWeaponBase> WeaponClass;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* InteractionSphere;

	class ANPCInteractable* CurrentNPC = nullptr;

	UFUNCTION()
	void OnInteractBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnInteractEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void Interact();
};
