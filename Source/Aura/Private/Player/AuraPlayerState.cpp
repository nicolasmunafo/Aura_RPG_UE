// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState()
{
	// Create the Ability System Component and Attribute Set
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);	// so that the ASC is replicated in multiplayer

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	
	// How often (per second) the server will try to update clients to sync up with the server
	// Normally this is low (half a second). It should be faster as the ASC and AS are on the player state
	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
