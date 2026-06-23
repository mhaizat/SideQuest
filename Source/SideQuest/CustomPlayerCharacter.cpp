#include "CustomPlayerCharacter.h"
#include "Components/CapsuleComponent.h"

ACustomPlayerCharacter::ACustomPlayerCharacter()
{
	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attributes"));
	WeaponManager = CreateDefaultSubobject<UWeaponManagerComponent>(TEXT("WeaponManager"));
	UIManager = CreateDefaultSubobject<UUIManagerComponent>(TEXT("UIManager"));
	QuestManager = CreateDefaultSubobject<UQuestManagerComponent>(TEXT("QuestManager"));
	DialogueComponent = CreateDefaultSubobject<UDialogueComponent>(TEXT("DialogueComponent"));
	GameStateManagerComponent = CreateDefaultSubobject<UGameStateManagerComponent>(TEXT("GameStateManagerComponent"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
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

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACustomPlayerCharacter::OnInteractBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ACustomPlayerCharacter::OnInteractEndOverlap);
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
	}
}

void ACustomPlayerCharacter::OnInteractEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ANPCInteractable* NPC = Cast<ANPCInteractable>(OtherActor);

	if (NPC && NPC == CurrentNPC)
	{
		CurrentNPC = nullptr;
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
	OnNotificationVisibilityChanged.Broadcast(true);
}

void ACustomPlayerCharacter::ClearCurrentNPC(ANPCInteractable* NPC)
{
	CurrentNPC = nullptr;
	OnNotificationVisibilityChanged.Broadcast(false);
}
