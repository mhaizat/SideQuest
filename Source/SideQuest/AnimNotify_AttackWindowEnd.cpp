#include "AnimNotify_AttackWindowEnd.h"

void UAnimNotify_AttackWindowEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	UE_LOG(LogTemp, Warning, TEXT("END NOTIFY FIRED"));

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	ACustomPlayerCharacter* Character = Cast<ACustomPlayerCharacter>(Owner);
	if (!Character) return;

	Character->AttackWindowEnd();
}