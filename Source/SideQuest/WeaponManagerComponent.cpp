#include "WeaponManagerComponent.h"
#include "CustomPlayerCharacter.h"

UWeaponManagerComponent::UWeaponManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* CharacterOwner = Cast<ACharacter>(GetOwner());
	if (!CharacterOwner) return;

	for (TSubclassOf<AWeaponBase> WeaponClass : WeaponInventory)
	{
		if (!WeaponClass) continue;

		AWeaponBase* NewWeapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass, CharacterOwner->GetActorTransform());
		if (!NewWeapon) continue;

		NewWeapon->AttachToComponent(CharacterOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("weapon"));
		NewWeapon->SetActorHiddenInGame(true);
		NewWeapon->SetActorEnableCollision(false);

		SpawnedWeapons.Add(NewWeapon);
	}
}

void UWeaponManagerComponent::EquipWeapon(int32 Index)
{
	if (bIsAttacking) return;
	if (!SpawnedWeapons.IsValidIndex(Index)) return;

	if (EquippedWeapon)
	{
		EquippedWeapon->SetActorHiddenInGame(true);
		EquippedWeapon->StopTrace();
	}

	CurrentWeaponIndex = Index;
	EquippedWeapon = SpawnedWeapons[Index];

	EquippedWeapon->SetActorHiddenInGame(false);
}

void UWeaponManagerComponent::NextWeapon()
{
	if (SpawnedWeapons.Num() == 0) return;

	int32 NextIndex = (CurrentWeaponIndex + 1) % SpawnedWeapons.Num();
	EquipWeapon(NextIndex);
}

void UWeaponManagerComponent::SetAttacking(bool bAttacking)
{
	bIsAttacking = bAttacking;
}

bool UWeaponManagerComponent::IsAttacking() const
{
	return bIsAttacking;
}

