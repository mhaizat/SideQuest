#include "CustomPlayerCharacter.h"

ACustomPlayerCharacter::ACustomPlayerCharacter()
{
	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attributes"));
}

void ACustomPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!Attributes) return;

	Attributes->TakeDamage(20.f);
}