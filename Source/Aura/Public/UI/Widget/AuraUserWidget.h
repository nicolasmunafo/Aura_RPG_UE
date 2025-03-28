// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;		// Pointer to the controller of the widget (it's UObject because the controller is an UObject)


protected:

	// As soon as the widget controller is set, we will call this function 
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();


	
};
