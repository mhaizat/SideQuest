#include "AnimNotify_AttackWindowStart.h"

void UAnimNotify_AttackWindowStart::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	UE_LOG(LogTemp, Warning, TEXT("START NOTIFY FIRED"));

	if (!MeshComp) return;

	UE_LOG(LogTemp, Warning, TEXT("START NOTIFY FIRED 2"));
	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	UE_LOG(LogTemp, Warning, TEXT("START NOTIFY FIRED 3"));

	ACustomPlayerCharacter* Character = Cast<ACustomPlayerCharacter>(Owner);
	if (!Character) return;

	UE_LOG(LogTemp, Warning, TEXT("START NOTIFY FIRED 4"));

	Character->AttackWindowStart();

}