#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, Health, float, MaxHealth);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIDEQUEST_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAttributeComponent();

protected:
	virtual void BeginPlay() override;

public:

	// =========================
	// HEALTH
	// =========================

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	float Health = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	float MaxHealth = 100.f;

	// =========================
	// STAMINA
	// =========================

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	float Stamina = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	float MaxStamina = 100.f;

	// =========================
	// EVENTS
	// =========================

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthChanged OnHealthChanged;

	// =========================
	// FUNCTIONS
	// =========================

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Damage);

	UFUNCTION(BlueprintCallable)
	void Heal(float Amount);

	UFUNCTION(BlueprintCallable)
	bool ConsumeStamina(float Amount);

	UFUNCTION(BlueprintCallable)
	void RestoreStamina(float Amount);

	bool IsAlive() const;
};