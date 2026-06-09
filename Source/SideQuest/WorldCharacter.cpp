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
		OnHitReact();
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

void AWorldCharacter::OnHitReact()
{
	UE_LOG(LogTemp, Warning, TEXT("%s hit reacted"), *GetName());
}

void AWorldCharacter::ReceiveHit(float Damage, FVector AttackDirection)
{
	if (Attributes)
	{
		Attributes->TakeDamage(Damage);
	}

	UE_LOG(LogTemp, Warning, TEXT("ReceiveHit CALLED"));

	OnHitReact();

	FVector Forward = GetActorForwardVector();

	float ForwardDot = FVector::DotProduct(Forward, -AttackDirection);
	float RightDot = FVector::DotProduct(GetActorRightVector(), AttackDirection);

	FString HitDirection = "Front";

	if (FMath::Abs(RightDot) > FMath::Abs(ForwardDot))
	{
		HitDirection = (RightDot > 0) ? "Right" : "Left";
	}
	else
	{
		HitDirection = (ForwardDot > 0) ? "Front" : "Back";
	}

	UE_LOG(LogTemp, Warning, TEXT("%s hit from %s"),
		*GetName(),
		*HitDirection);
}
