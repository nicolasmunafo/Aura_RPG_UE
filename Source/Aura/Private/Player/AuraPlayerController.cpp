// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;		// When an entity changes on the server, the change will replicate or be sent down to the client

}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);		// Assert that the Aura Context is set

	// To include the Input Mapping Context, we have to access it through the Enhanced Input Local Player Subsystem
	// Subsystems are singletons
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);	
	Subsystem->AddMappingContext(AuraContext, 0);

	// Show mouse cursor with a default cursor
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	// Change the input mode of the player controller with configuration such as do not lock mouse to viewport and do not hide cursor during capture
	FInputModeGameAndUI InputModeData;	// Create an Input Mode Data variable
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);	// Set the input mode of the current player controller to the one created



	

}
