#include "UIManagerComponent.h"

UUIManagerComponent::UUIManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UUIManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// -------------------------
	// Create all widgets
	// -------------------------
	for (const auto& Pair : WidgetClasses)
	{
		if (!Pair.Value) continue;

		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), Pair.Value);
		if (!Widget) continue;

		Widget->AddToViewport();
		Widget->SetVisibility(ESlateVisibility::Hidden);

		WidgetInstances.Add(Pair.Key, Widget);
	}

	// Optional: start in Gameplay state
	SetUIState(EUIState::Gameplay);
}

// -------------------------
// Widget lookup
// -------------------------
UUserWidget* UUIManagerComponent::GetWidget(FName WidgetID) const
{
	if (UUserWidget* const* Found = WidgetInstances.Find(WidgetID))
	{
		return *Found;
	}

	return nullptr;
}

// -------------------------
// Basic show/hide
// -------------------------
void UUIManagerComponent::ShowWidget(FName WidgetID)
{
	if (UUserWidget* Widget = GetWidget(WidgetID))
	{
		//Widget->AddToViewport();
		Widget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UUIManagerComponent::HideWidget(FName WidgetID)
{
	if (UUserWidget* Widget = GetWidget(WidgetID))
	{
		//Widget->RemoveFromViewport();
		Widget->SetVisibility(ESlateVisibility::Collapsed);

		UE_LOG(LogTemp, Warning,
			TEXT("Current Visibility: %d"),
			(int32)Widget->GetVisibility());
		//UE_LOG(LogTemp, Warning, TEXT("HideWidget"));
	}

	UE_LOG(LogTemp, Warning, TEXT("UIManager hiding Dialogue widget"));
}

// -------------------------
// STATE MACHINE CORE
// -------------------------
void UUIManagerComponent::SetUIState(EUIState NewState)
{
	if (CurrentState == NewState) return;

	// Hide previous state widget
	if (StateWidgets.Contains(CurrentState))
	{
		FName OldWidgetID = StateWidgets[CurrentState];

		if (UUserWidget* OldWidget = GetWidget(OldWidgetID))
		{
			OldWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	// Show new state widget
	if (StateWidgets.Contains(NewState))
	{
		FName NewWidgetID = StateWidgets[NewState];

		if (UUserWidget* NewWidget = GetWidget(NewWidgetID))
		{
			NewWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}

	CurrentState = NewState;
}