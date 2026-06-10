#include "CustomPlayerCharacter.h"

ACustomPlayerCharacter::ACustomPlayerCharacter()
{
	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attributes"));
	WeaponManager = CreateDefaultSubobject<UWeaponManagerComponent>(TEXT("WeaponManager"));

	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	if (!InteractionSphere) return;

	InteractionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionSphere->SetGenerateOverlapEvents(true);

	InteractionSphere->SetCollisionObjectType(ECC_Pawn);

	InteractionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	InteractionSphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	InteractionSphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);

	QuestManager = CreateDefaultSubobject<UQuestManagerComponent>(TEXT("QuestManager"));
}

void ACustomPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ACustomPlayerCharacter::Attack);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ACustomPlayerCharacter::Interact);
	}
}

void ACustomPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &ACustomPlayerCharacter::OnInteractBeginOverlap);
	InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &ACustomPlayerCharacter::OnInteractEndOverlap);
}

void ACustomPlayerCharacter::Attack()
{
	if (!AttackMontage || !WeaponManager) return;

	AWeaponBase* CurrentWeapon = WeaponManager->GetCurrentEquippedWeapon();

	if (!CurrentWeapon)
	{
		return;
	}

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

void ACustomPlayerCharacter::OnInteractBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ANPCInteractable* NPC = Cast<ANPCInteractable>(OtherActor);

	if (NPC)
	{
		CurrentNPC = NPC;
		UE_LOG(LogTemp, Warning, TEXT("NPC in range"));
	}
}

void ACustomPlayerCharacter::OnInteractEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ANPCInteractable* NPC = Cast<ANPCInteractable>(OtherActor);

	if (NPC && NPC == CurrentNPC)
	{
		CurrentNPC = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("NPC out of range"));
	}
}

void ACustomPlayerCharacter::Interact()
{
	if (CurrentNPC)
	{
		CurrentNPC->Interact(this);
	}
}

void ACustomPlayerCharacter::SetCurrentNPC(ANPCInteractable* NPC)
{
	CurrentNPC = NPC;
}

void ACustomPlayerCharacter::ClearCurrentNPC(ANPCInteractable* NPC)
{
	CurrentNPC = nullptr;
}
