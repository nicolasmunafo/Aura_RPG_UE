// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

// Forward declarations
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	// To retrieve the data associated to input, we have to setup an input component (which was in the character controller)
	virtual void SetupInputComponent() override;
	
private:
	// To associate the IMC created in the UE editor
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	// To associate the Input Action/IA created in the UE editor
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	// Reads the data as an input action value
	void Move(const FInputActionValue& InputActionValue);

	// To detect the movement of the cursor
	void CursorTrace();
	IEnemyInterface* LastActor;	// Pointer to the last actor that was highlighted (to unhighlight if it was highlighted)
	IEnemyInterface* ThisActor;	// Pointer to the current actor that is highlighted 

};
