#include "CustomPlayerCharacter.h"

ACustomPlayerCharacter::ACustomPlayerCharacter()
{
	//GetMesh()->SetupAttachment(GetCapsuleComponent());
	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attributes"));
}

void ACustomPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ACustomPlayerCharacter::Attack);
	}
}

void ACustomPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (WeaponClass)
	{
		EquippedWeapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass);

		if (!EquippedWeapon) return;

		EquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("weapon")); // we will create this
		EquippedWeapon->SetOwner(this);
	}
}

void ACustomPlayerCharacter::Attack()
{
	if (!AttackMontage) return;

	PlayAnimMontage(AttackMontage);
}

void ACustomPlayerCharacter::AttackWindowStart()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->StartTrace();

		UE_LOG(LogTemp, Warning, TEXT("AttackWindowStart FIRED"));
	}
}

void ACustomPlayerCharacter::AttackWindowEnd()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->StopTrace();

		UE_LOG(LogTemp, Warning, TEXT("AttackWindowEnd FIRED"));
	}
}