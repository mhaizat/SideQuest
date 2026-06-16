#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Blueprint/UserWidget.h"
#include "QuestTrackerWidget.h"
#include "UIManagerComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIDEQUEST_API UUIManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UUIManagerComponent();

	virtual void BeginPlay() override;

	// -------------------------
	// Widget System
	// -------------------------
	UUserWidget* GetWidget(FName WidgetID) const;

	// -------------------------
	// Visibility Control
	// -------------------------
	void ShowWidget(FName WidgetID);
	void HideWidget(FName WidgetID);

protected:

	// Widget class registry (setup in editor)
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TMap<FName, TSubclassOf<UUserWidget>> WidgetClasses;

	// Runtime widget storage
	UPROPERTY(VisibleAnywhere)
	TMap<FName, UUserWidget*> WidgetInstances;
};