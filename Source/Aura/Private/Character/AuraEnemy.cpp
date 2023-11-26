// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"

AAuraEnemy::AAuraEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAuraEnemy::HighlightActor()
{
	bHighlighted = true;
}

void AAuraEnemy::UnHighlightActor()
{
	bHighlighted = false;
}

void AAuraEnemy::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	
	if (bHighlighted) {
		FVector SpherePosition = GetActorLocation();
		DrawDebugSphere(GetWorld(), SpherePosition, 20.f, 16, FColor::Blue);
	}
}
