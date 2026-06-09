#include "WorldCharacter.h"

AWorldCharacter::AWorldCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attributes"));
}

void AWorldCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!Attributes) return;

	Attributes->OnDeath.AddDynamic(this, &AWorldCharacter::Die);
}

void AWorldCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AWorldCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (Attributes)
	{
		Attributes->TakeDamage(DamageAmount);

		UE_LOG(LogTemp, Warning, TEXT("%s took %f damage"), *GetName(), DamageAmount);
	}

	return DamageAmount;
}

void AWorldCharacter::Die()
{
	UE_LOG(LogTemp, Warning, TEXT("%s died"), *GetName());

	// basic behavior for now
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(5.f);
}

