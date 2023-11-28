// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"
#include "Aura/Aura.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraEnemy::AAuraEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);	// To block visibility of the mesh (to highlight enemies with the cursor)

	// Create the Ability System Component and Attribute Set
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);	// so that the ASC is replicated in multiplayer
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);	// Only replicate cues, effects will be in the server

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AAuraEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	// Another way is just getting "Weapon" as it is part of the AuraCharacter
	USkeletalMeshComponent* WeaponComp = Cast<USkeletalMeshComponent>(GetMesh()->GetChildComponent(0));
	WeaponComp->SetRenderCustomDepth(true);
	WeaponComp->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	//bHighlighted = true;
}

void AAuraEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	GetMesh()->SetCustomDepthStencilValue(0);
	USkeletalMeshComponent* WeaponComp = Cast<USkeletalMeshComponent>(GetMesh()->GetChildComponent(0));
	WeaponComp->SetRenderCustomDepth(false);
	WeaponComp->SetCustomDepthStencilValue(0);
	
	//bHighlighted = false;
}

void AAuraEnemy::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	
	/*if (bHighlighted) {
		FVector SpherePosition = GetActorLocation();
		DrawDebugSphere(GetWorld(), SpherePosition, 20.f, 16, FColor::Blue);
	}*/
}
