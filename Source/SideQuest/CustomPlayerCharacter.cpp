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

	//if (WeaponClass)
	//{
	//	EquippedWeapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass);

	//	if (!EquippedWeapon) return;

	//	EquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("weapon")); // we will create this
	//	EquippedWeapon->SetOwner(this);
	//}
}

void ACustomPlayerCharacter::Attack()
{
	if (!AttackMontage) return;
	PlayAnimMontage(AttackMontage);
}

void ACustomPlayerCharacter::AttackWindowStart()
{
	if (!EquippedWeapon) return;
	EquippedWeapon->StartTrace();
}

void ACustomPlayerCharacter::AttackWindowEnd()
{
	if (!EquippedWeapon) return;
	EquippedWeapon->StopTrace();
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