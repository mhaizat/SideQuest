#include "UIManagerComponent.h"

UUIManagerComponent::UUIManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UUIManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	for (const auto& Pair : WidgetClasses)
	{
		if (!Pair.Value) continue;

		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), Pair.Value);
		if (!Widget) continue;

		Widget->AddToViewport();
		Widget->SetVisibility(ESlateVisibility::Hidden);

		WidgetInstances.Add(Pair.Key, Widget);

		if (UHUDWidget* HUDWidget = Cast<UHUDWidget>(Widget))
		{
			HUDWidget->InitializeHUDWidget(this);
		}
	}
}

UUserWidget* UUIManagerComponent::GetWidget(FName WidgetID) const
{
	if (UUserWidget* const* Found = WidgetInstances.Find(WidgetID))
	{
		return *Found;
	}

	return nullptr;
}

void UUIManagerComponent::ShowWidget(FName WidgetID)
{
	UUserWidget* Widget = GetWidget(WidgetID);
	if (!Widget) return;
	
	CurrentWidget = Widget;
	CurrentWidget->SetVisibility(ESlateVisibility::Visible);
}

void UUIManagerComponent::HideWidget(FName WidgetID)
{
	if (UUserWidget* Widget = GetWidget(WidgetID))
	{
		Widget->SetVisibility(ESlateVisibility::Collapsed);
	}
}
