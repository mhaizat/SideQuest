#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AttributeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "WorldCharacter.generated.h"

UCLASS()
class SIDEQUEST_API AWorldCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AWorldCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void Die();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAttributeComponent* Attributes;
};
