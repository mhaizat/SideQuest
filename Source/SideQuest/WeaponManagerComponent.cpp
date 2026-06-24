#include "WeaponManagerComponent.h"
#include "CustomPlayerCharacter.h"

UWeaponManagerComponent::UWeaponManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponManagerComponent::EquipItem(const FItemInstance& Item)
{
	// 1. Store item
	EquippedItem = Item;

	ACharacter* CharacterOwner = Cast<ACharacter>(GetOwner());
	if (!CharacterOwner) return;

	// 2. Remove old weapon
	if (EquippedWeapon)
	{
		EquippedWeapon->Destroy();
		EquippedWeapon = nullptr;
	}

	// 3. TEMP: map weapon type → class
	TSubclassOf<AWeaponBase> WeaponClass = nullptr;

	switch (Item.WeaponType)
	{
	case EWeaponTypes::Sword:
		WeaponClass = SwordClass;
		break;

	case EWeaponTypes::Axe:
		WeaponClass = AxeClass;
		break;

	case EWeaponTypes::Hammer:
		WeaponClass = HammerClass;
		break;
	}

	if (!WeaponClass) return;

	// 4. Spawn weapon
	AWeaponBase* NewWeapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass, CharacterOwner->GetActorTransform());
	if (!NewWeapon) return;

	// 5. Attach weapon
	NewWeapon->AttachToComponent(CharacterOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("weapon"));
	NewWeapon->SetActorHiddenInGame(false);
	NewWeapon->SetActorEnableCollision(false);

	EquippedWeapon = NewWeapon;

	// 6. Apply stats
	float FinalDamage = Item.BaseDamage;

	for (const FAffixInstance& Affix : Item.Affixes)
	{
		switch (Affix.Type)
		{
		case EAffixType::BonusDamage:
			FinalDamage += Affix.Value;
			break;

		default:
			break;
		}
	}

	EquippedWeapon->SetDamage(FinalDamage);

	UE_LOG(LogTemp, Warning, TEXT("Equipped item weapon: %s | Damage: %.2f"), *UEnum::GetValueAsString(Item.WeaponType), FinalDamage);
}

void UWeaponManagerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWeaponManagerComponent::SetAttacking(bool bAttacking)
{
	bIsAttacking = bAttacking;
	UE_LOG(LogTemp, Warning, TEXT("Attack 4"));

}

bool UWeaponManagerComponent::IsAttacking() const
{
	return bIsAttacking;
}

