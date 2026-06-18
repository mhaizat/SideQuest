#include "GameStateManagerComponent.h"
#include "UIManagerComponent.h"
#include "CustomPlayerCharacter.h"

void UGameStateManagerComponent::SetState(EGameState NewState)
{
	if (CurrentState == NewState) return;

	CurrentState = NewState;

	ApplyState(NewState);
}

void UGameStateManagerComponent::ApplyState(EGameState NewState)
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;

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
			PlayerController->SetShowMouseCursor(false);

			FInputModeGameOnly InputMode;
			PlayerController->SetInputMode(InputMode);
			PlayerController->SetIgnoreMoveInput(false);
			PlayerController->SetIgnoreLookInput(false);

			UIManagerComponent->ShowWidget("HUD");
			break;
		}

		case EGameState::UIOnly:
		{
			PlayerController->SetShowMouseCursor(true);

			FInputModeGameAndUI InputMode;
			InputMode.SetHideCursorDuringCapture(false);

			PlayerController->SetInputMode(InputMode);
			PlayerController->SetIgnoreMoveInput(true);
			PlayerController->SetIgnoreLookInput(true);

			UIManagerComponent->HideWidget("HUD");
			break;
		}

		case EGameState::GameAndUI:
		{
			PlayerController->SetShowMouseCursor(true);
			break;
		}

		default:
			break;
	}
}

