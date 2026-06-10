#include "NPCBase.h"

ANPCBase::ANPCBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

void ANPCBase::BeginPlay()
{
	Super::BeginPlay();
}

void ANPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
