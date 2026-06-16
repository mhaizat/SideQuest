#include "GameStateManagerComponent.h"

void UGameStateManagerComponent::SetState(EGameState NewState)
{
	if (CurrentState == NewState)
	{
		return;
	}

	CurrentState = NewState;

	ApplyState(NewState);
}

void UGameStateManagerComponent::ApplyState(EGameState NewState)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC)
	{
		return;
	}

	switch (NewState)
	{
	case EGameState::Gameplay:
	{
		PC->SetShowMouseCursor(false);

		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);

		PC->SetIgnoreMoveInput(false);
		PC->SetIgnoreLookInput(false);

		break;
	}

	case EGameState::Dialogue:
	{
		PC->SetShowMouseCursor(true);

		FInputModeGameAndUI InputMode;
		InputMode.SetHideCursorDuringCapture(false);
		PC->SetInputMode(InputMode);

		PC->SetIgnoreMoveInput(true);
		PC->SetIgnoreLookInput(true);

		break;
	}

	case EGameState::Inventory:
	{
		PC->SetShowMouseCursor(true);

		FInputModeGameAndUI InputMode;
		InputMode.SetHideCursorDuringCapture(false);
		PC->SetInputMode(InputMode);

		PC->SetIgnoreMoveInput(true);
		PC->SetIgnoreLookInput(true);

		break;
	}

	case EGameState::Pause:
	{
		PC->SetShowMouseCursor(true);

		FInputModeUIOnly InputMode;
		PC->SetInputMode(InputMode);

		PC->SetIgnoreMoveInput(true);
		PC->SetIgnoreLookInput(true);

		break;
	}

	default:
		break;
	}
}

