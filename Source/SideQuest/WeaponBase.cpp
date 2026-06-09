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

	if (!bCanTrace) return;

	PerformTrace();
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
		FVector AttackDirection = (Hit.GetActor()->GetActorLocation() - OwnerActor->GetActorLocation()).GetSafeNormal();

		UE_LOG(LogTemp, Warning, TEXT("Attack Dir: %s"), *AttackDirection.ToString());

		if (!HitActors.Contains(Hit.GetActor()))
		{
			HitActors.Add(Hit.GetActor());

			IDamageInterface* Damageable = Cast<IDamageInterface>(Hit.GetActor());
			if (!Damageable) return;

			FVector AttackDir = (Hit.GetActor()->GetActorLocation() - OwnerActor->GetActorLocation()).GetSafeNormal();
			Damageable->ReceiveHit(20.f, AttackDir);
		}
	}

	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.f, 0, 2.f);
}

