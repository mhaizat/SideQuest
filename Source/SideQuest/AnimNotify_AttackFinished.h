#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CustomPlayerCharacter.h"
#include "AnimNotify_AttackFinished.generated.h"

UCLASS()
class SIDEQUEST_API UAnimNotify_AttackFinished : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
