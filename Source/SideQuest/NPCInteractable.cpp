#include "NPCInteractable.h"
#include "CustomPlayerCharacter.h"

ANPCInteractable::ANPCInteractable()
{
	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	SetRootComponent(InteractionSphere);

	InteractionSphere->InitSphereRadius(150.f);

	InteractionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionSphere->SetGenerateOverlapEvents(true);

	InteractionSphere->SetCollisionObjectType(ECC_WorldDynamic);
	InteractionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void ANPCInteractable::Interact(AActor* Interactor)
{
	UE_LOG(LogTemp, Warning, TEXT("Base NPC Interaction"));
}

void ANPCInteractable::BeginPlay()
{
	Super::BeginPlay();

	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &ANPCInteractable::OnPlayerEnter);
	InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &ANPCInteractable::OnPlayerExit);
}

void ANPCInteractable::OnPlayerEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACustomPlayerCharacter* Player = Cast<ACustomPlayerCharacter>(OtherActor);

	if (Player)
	{
		Player->SetCurrentNPC(this);
		UE_LOG(LogTemp, Warning, TEXT("Player entered NPC range"));
	}
}

void ANPCInteractable::OnPlayerExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACustomPlayerCharacter* Player = Cast<ACustomPlayerCharacter>(OtherActor);

	if (Player)
	{
		Player->ClearCurrentNPC(this);
		UE_LOG(LogTemp, Warning, TEXT("Player left NPC range"));
	}
}