// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerState.h"

AAuraPlayerState::AAuraPlayerState()
{
	// How often (per second) the server will try to update clients to sync up with the server
	// Normally this is low (half a second). It should be faster as the ASC and AS are on the player state
	NetUpdateFrequency = 100.f;
}
