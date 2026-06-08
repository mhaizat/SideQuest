#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CustomPlayerCharacter.h"
#include "AnimNotify_AttackWindowStart.generated.h"

UCLASS()
class SIDEQUEST_API UAnimNotify_AttackWindowStart : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
