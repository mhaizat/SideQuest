#include "WeaponBase.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

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

	Super::Tick(DeltaTime);

	if (bCanTrace)
	{
		PerformTrace();
	}
}

void AWeaponBase::StartTrace()
{
	HitActors.Empty();
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

	FVector Start = WeaponMesh->GetComponentLocation();
	FVector Forward = WeaponMesh->GetForwardVector();
	FVector End = Start + Forward * 120.f;

	TArray<AActor*> Ignore;
	Ignore.Add(OwnerActor);

	FHitResult Hit;

	bool bHit = UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Start, End, 20.f, UEngineTypes::ConvertToTraceType(ECC_Pawn), false, Ignore, EDrawDebugTrace::ForDuration, Hit, true);
		
	if (bHit && Hit.GetActor())
	{
		if (!HitActors.Contains(Hit.GetActor()))
		{
			HitActors.Add(Hit.GetActor());

			UGameplayStatics::ApplyDamage(Hit.GetActor(), 20.f, GetOwner()->GetInstigatorController(), this, nullptr);
		}
	}

	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.f, 0, 2.f);
}

