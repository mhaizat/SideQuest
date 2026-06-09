#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageInterface.generated.h"

UINTERFACE(MinimalAPI)
class UDamageInterface : public UInterface
{
	GENERATED_BODY()
};

class SIDEQUEST_API IDamageInterface
{
	GENERATED_BODY()

public:

	virtual void ReceiveHit(float Damage, FVector AttackDirection) = 0;
};
