// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;	// Rotate the character towards the acceleration vector
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);	
	GetCharacterMovement()->bConstrainToPlane = true;	// Constrain the movement to a plane
	GetCharacterMovement()->bSnapToPlaneAtStart = true;	// for a Top down game

	// The character itself shouldn't use the controller's rotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

}
