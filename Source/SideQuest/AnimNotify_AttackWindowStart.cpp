#include "AnimNotify_AttackWindowStart.h"

void UAnimNotify_AttackWindowStart::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	UE_LOG(LogTemp, Warning, TEXT("START NOTIFY FIRED"));

	if (!MeshComp) return;

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	ACustomPlayerCharacter* Character = Cast<ACustomPlayerCharacter>(Owner);
	if (!Character) return;

	Character->AttackWindowStart();
}