#include "CustomPlayerCharacter.h"

ACustomPlayerCharacter::ACustomPlayerCharacter()
{
	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attributes"));
	WeaponManager = CreateDefaultSubobject<UWeaponManagerComponent>(TEXT("WeaponManager"));
}

void ACustomPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ACustomPlayerCharacter::Attack);
		EnhancedInputComponent->BindAction(Slot1Action, ETriggerEvent::Started, this, &ACustomPlayerCharacter::EquipWeaponSlot1);
		EnhancedInputComponent->BindAction(Slot2Action, ETriggerEvent::Started, this, &ACustomPlayerCharacter::EquipWeaponSlot2);
	}
}

void ACustomPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ACustomPlayerCharacter::Attack()
{
	if (!AttackMontage || !WeaponManager) return;

	WeaponManager->SetAttacking(true);

	PlayAnimMontage(AttackMontage);
}

void ACustomPlayerCharacter::AttackWindowStart()
{
	if (!WeaponManager)
	{
		return;
	}

	AWeaponBase* CurrentWeapon = WeaponManager->GetCurrentEquippedWeapon();

	if (!CurrentWeapon)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("AttackWindowStart Started"));

	CurrentWeapon->StartTrace();
}

void ACustomPlayerCharacter::AttackWindowEnd()
{
	if (!WeaponManager)
	{
		return;
	}

	AWeaponBase* CurrentWeapon = WeaponManager->GetCurrentEquippedWeapon();

	if (!CurrentWeapon)
	{
		return;
	}

	CurrentWeapon->StopTrace();
}

void ACustomPlayerCharacter::EquipWeaponSlot1()
{
	if (WeaponManager)
	{
		WeaponManager->EquipWeapon(0);
	}
}

void ACustomPlayerCharacter::EquipWeaponSlot2()
{
	if (WeaponManager)
	{
		WeaponManager->EquipWeapon(1);
	}
}

void ACustomPlayerCharacter::AttackFinished()
{
	if (WeaponManager)
	{
		WeaponManager->SetAttacking(false);
	}

	UE_LOG(LogTemp, Warning, TEXT("Attack Finished"));
}