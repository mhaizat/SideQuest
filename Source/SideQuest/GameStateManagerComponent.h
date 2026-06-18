#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameStateManagerComponent.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	Gameplay,
	UIOnly,
	GameAndUI
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIDEQUEST_API UGameStateManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetState(EGameState NewState);

	UFUNCTION(BlueprintPure)
	EGameState GetCurrentState() const { return CurrentState; }

private:
	void ApplyState(EGameState NewState);

	UPROPERTY()
	EGameState CurrentState = EGameState::Gameplay;
};
