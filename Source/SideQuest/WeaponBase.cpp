#include "WeaponBase.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(Root);

	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	WeaponMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	WeaponMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::StartTrace()
{
	bCanTrace = true;
}

void AWeaponBase::StopTrace()
{
	bCanTrace = false;
}

void AWeaponBase::PerformTrace()
{
	if (!bCanTrace) return;

	AActor* OwnerActor = GetOwner();
	if (!OwnerActor) return;

	FVector Start = OwnerActor->GetActorLocation() + FVector(0, 0, 50.f);
	FVector End = Start + OwnerActor->GetActorForwardVector() * 120.f;
	FVector Forward = OwnerActor->GetActorForwardVector();

	TArray<AActor*> Ignore;
	Ignore.Add(OwnerActor);

	FHitResult Hit;

	bool bHit = UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Start, End, 20.f, UEngineTypes::ConvertToTraceType(ECC_Pawn), false, Ignore, EDrawDebugTrace::ForDuration, Hit, true);
		
	if (bHit && Hit.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *Hit.GetActor()->GetName());
	}
}

