#include "AttributeComponent.h"

UAttributeComponent::UAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	Stamina = MaxStamina;
}

void UAttributeComponent::TakeDamage(float Damage)
{
	if (Damage <= 0.f || Health <= 0.f) return;

	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);

	OnHealthChanged.Broadcast(Health, MaxHealth);

	if (Health <= 0.f)
	{
		OnDeath.Broadcast();
	}
}

void UAttributeComponent::Heal(float Amount)
{
	if (Amount <= 0.f || Health <= 0.f) return;

	Health = FMath::Clamp(Health + Amount, 0.f, MaxHealth);

	OnHealthChanged.Broadcast(Health, MaxHealth);
}

bool UAttributeComponent::ConsumeStamina(float Amount)
{
	if (Amount <= 0.f || Stamina < Amount) return false;

	Stamina = FMath::Clamp(Stamina - Amount, 0.f, MaxStamina);
	return true;
}

void UAttributeComponent::RestoreStamina(float Amount)
{
	if (Amount <= 0.f) return;

	Stamina = FMath::Clamp(Stamina + Amount, 0.f, MaxStamina);
}

bool UAttributeComponent::IsAlive() const
{
	return Health > 0.f;
}