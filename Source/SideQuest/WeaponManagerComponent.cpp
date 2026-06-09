#include "WeaponManagerComponent.h"
#include "CustomPlayerCharacter.h"

UWeaponManagerComponent::UWeaponManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	//if (WeaponInventory.Num() > 0)
	//{
	//	EquipWeapon(0);
	//}
}

void UWeaponManagerComponent::EquipWeapon(int32 Index)
{
	if (bIsAttacking || !WeaponInventory.IsValidIndex(Index)) return;

	DestroyCurrentWeapon();
	SpawnWeapon(Index);

	CurrentWeaponIndex = Index;
}

void UWeaponManagerComponent::NextWeapon()
{
	if (WeaponInventory.Num() == 0) return;

	int32 NextIndex = (CurrentWeaponIndex + 1) % WeaponInventory.Num();
	EquipWeapon(NextIndex);
}

void UWeaponManagerComponent::SpawnWeapon(int32 Index)
{
	AActor* Owner = GetOwner();
	if (!Owner) return;

	FActorSpawnParameters Params;
	Params.Owner = Owner;
	Params.Instigator = Owner->GetInstigator();

	EquippedWeapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponInventory[Index], Owner->GetActorTransform(), Params);
	if (!EquippedWeapon) return;

	//! NOTE: attach to character mesh
	ACharacter* CharacterOwner = Cast<ACharacter>(Owner);
	if (!CharacterOwner) return;

	EquippedWeapon->AttachToComponent(CharacterOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("weapon"));
}

void UWeaponManagerComponent::DestroyCurrentWeapon()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->Destroy();
		EquippedWeapon = nullptr;
	}
}

void UWeaponManagerComponent::SetAttacking(bool bAttacking)
{
	bIsAttacking = bAttacking;
}

bool UWeaponManagerComponent::IsAttacking() const
{
	return bIsAttacking;
}

