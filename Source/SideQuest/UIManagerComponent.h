#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Blueprint/UserWidget.h"
#include "QuestTrackerWidget.h"
#include "HUDWidget.h"
#include "UIManagerComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIDEQUEST_API UUIManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UUIManagerComponent();

	virtual void BeginPlay() override;

	UUserWidget* GetWidget(FName WidgetID) const;
	UUserWidget* GetCurrentWidget() { return CurrentWidget; }
	void SetCurrentWidget(UUserWidget* InCurrentWidget) { CurrentWidget = InCurrentWidget; }

	void ShowWidget(FName WidgetID);
	void HideWidget(FName WidgetID);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TMap<FName, TSubclassOf<UUserWidget>> WidgetClasses;

	UPROPERTY(VisibleAnywhere)
	TMap<FName, UUserWidget*> WidgetInstances;

	UUserWidget* CurrentWidget;
};