#include "QuestItem.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CustomPlayerCharacter.h"
#include "QuestManagerComponent.h"

AQuestItem::AQuestItem()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(Root);
	CollisionSphere->SetSphereRadius(100.f);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionSphere->SetGenerateOverlapEvents(true);
	CollisionSphere->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AQuestItem::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AQuestItem::OnOverlapBegin);
}

void AQuestItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACustomPlayerCharacter* Player = Cast<ACustomPlayerCharacter>(OtherActor);
	if (!Player) return;

	UQuestManagerComponent* QuestManager = Player->GetQuestManager();
	if (!QuestManager) return;

	if (!QuestManager->HasRelevantQuest(ItemID))
	{
		UE_LOG(LogTemp, Warning, TEXT("No quest uses this item"));
		return;
	}

	QuestManager->AddProgress(ItemID);

	UE_LOG(LogTemp, Warning, TEXT("Picked up: %s"), *ItemID.ToString());
		
	Destroy();
}
