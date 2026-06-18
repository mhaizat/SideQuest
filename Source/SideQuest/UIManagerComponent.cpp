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

		UE_LOG(LogTemp, Warning, TEXT("INSERTING KEY: '%s'"), *Pair.Key.ToString());
		UE_LOG(LogTemp, Warning, TEXT("REQUESTING KEY: '%s'"), TEXT("Quest"));

		WidgetInstances.Add(Pair.Key, Widget);

		if (UHUDWidget* HUDWidget = Cast<UHUDWidget>(Widget))
		{
			HUDWidget->InitializeHUDWidget(this);
			UE_LOG(LogTemp, Warning, TEXT("HUD Casted"));

		}
	}
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
	UE_LOG(LogTemp, Warning, TEXT("ShowWidget 1"));

	UUserWidget* Widget = GetWidget(WidgetID);
	if (!Widget) return;
	
	UE_LOG(LogTemp, Warning, TEXT("ShowWidget 2"));

	CurrentWidget = Widget;
	CurrentWidget->SetVisibility(ESlateVisibility::Visible);
}

void UUIManagerComponent::HideWidget(FName WidgetID)
{
	if (UUserWidget* Widget = GetWidget(WidgetID))
	{
		//Widget->RemoveFromViewport();
		Widget->SetVisibility(ESlateVisibility::Collapsed);

		UE_LOG(LogTemp, Warning, TEXT("Current Visibility: %d"), (int32)Widget->GetVisibility());
		//UE_LOG(LogTemp, Warning, TEXT("HideWidget"));
	}

	UE_LOG(LogTemp, Warning, TEXT("UIManager hiding Dialogue widget"));
}
