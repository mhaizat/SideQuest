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
	UE_LOG(LogTemp, Warning, TEXT("TRACE STARTED"));

	HitActors.Empty();
	bCanTrace = true;
}

void AWeaponBase::StopTrace()
{
	bCanTrace = false;
}

void AWeaponBase::PerformTrace()
{
	UE_LOG(LogTemp, Warning, TEXT("TRACE RUNNING 1"));
	
	if (!bCanTrace) return;

	UE_LOG(LogTemp, Warning, TEXT("TRACE RUNNING 2"));

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

			FHitData HitData;

			HitData.Damage = 20.f;
			HitData.AttackDirection = AttackDir;
			HitData.InstigatorActor = OwnerActor;
			HitData.Weapon = this;

			Damageable->ReceiveHit(HitData);
		}
	}

	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.f, 0, 2.f);
}

