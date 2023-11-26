// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

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

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// To bind a function to the input action, we have to cast the InputComponent to an Enhanced Input Component
	// CastChecked casts the variable to a specific type and asserts if the cast fails
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	// Bind the function "Move" to the "MoveAction" action when it is triggered
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);



}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	// Get the XY axis from the input
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
}
