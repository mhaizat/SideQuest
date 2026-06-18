#include "GameStateManagerComponent.h"
#include "UIManagerComponent.h"
#include "CustomPlayerCharacter.h"

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

	ACustomPlayerCharacter* Player = Cast<ACustomPlayerCharacter>(GetOwner());
	if (!Player) return;

	UGameStateManagerComponent* GameStateManagerComponent = Player->GetGameStateManagerComponent();
	if (!GameStateManagerComponent) return;

	UUIManagerComponent* UIManagerComponent = Player->GetUIManager();
	if (!UIManagerComponent) return;

	switch (NewState)
	{
	case EGameState::Gameplay:
	{
		PC->SetShowMouseCursor(false);

		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);

		PC->SetIgnoreMoveInput(false);
		PC->SetIgnoreLookInput(false);

		UIManagerComponent->ShowWidget("HUD");
		break;
	}

	case EGameState::UIOnly:
	{
		PC->SetShowMouseCursor(true);

		FInputModeGameAndUI InputMode;
		InputMode.SetHideCursorDuringCapture(false);
		PC->SetInputMode(InputMode);

		PC->SetIgnoreMoveInput(true);
		PC->SetIgnoreLookInput(true);

		UIManagerComponent->HideWidget("HUD");

		break;
	}

	case EGameState::GameAndUI:
	{
		PC->SetShowMouseCursor(true);
		break;
	}


	default:
		break;
	}
}

