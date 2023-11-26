// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;		// When an entity changes on the server, the change will replicate or be sent down to the client

}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();	// It will get the hit result from the cursor


}


void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, CursorHit);	// Performs a trace from the cursor to the map and checks if there is a hit

	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;	// Store the previous actor that was highlighted
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());	// Get the current actor that has been hit under the cursor trace

	/** 
	*	Line trace from cursor. There are several scenarios:
	* A. LastActor is null && ThisActor is null
	*			- Do nothing
	* B. LastActor is null && ThisActor is valid
	*			- Highlight ThisActor
	* C. LastActor is valid && ThisActor is null
	*			- UnHighlight LastActor
	* D. LastActor is valid && ThisActor is valid but LastActor != ThisActor
	*			- UnHighlight LastActor
	*			- Highlight ThisActor
	* E. LastActor is valid && ThisActor is valid && LastActor == ThisActor
	*			- Do nothing
	* 
	*/

	if (LastActor == nullptr) {
		if (ThisActor != nullptr) {
			// Case B

			ThisActor->HighlightActor();
		}
		else {
			// Case A - Both are null, do nothing
		}
	}
	else { // LastActor is valid
		if (ThisActor == nullptr) {
			// Case C
			LastActor->UnHighlightActor();
		}
		else { // Both actors are valid
			if (LastActor != ThisActor) {
				// Case D
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else {
				// Case E - Do nothing
			}
		}
	}




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

	// Add movement to the controlled pawn in the forward and right direction based on the FVector2
	// We have to get the direction of the controller to know what is forward
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);		// To store only the yaw (rotation in XY plane)

	// To get the forward and right normalized vectors from the rotator
	// The controller's rotation is the rotation of the vector from the camera to the character
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// Do not assert because move can be called many times per tick
	if (APawn* ControlledPawn = GetPawn<APawn>()) {
		// Add movement considering the forward direction with the scale given by the Y vector from the input action (W or S)
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);

		// Add movement considering the right direction with the scale given by the X vector from the input action (A or D)
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);

	}

}
