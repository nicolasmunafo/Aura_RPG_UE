// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AuraCharacterBase.generated.h"

// Forward declarations
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)	//Prevents the class to be added into the level
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet;	};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*
		Weapon as skeletal mesh component
		Like a raw pointer, has access tracking (track how often the pointer is accessed) and lazy loading (an asset cannot be loaded until it's actually needed
		UPROPERTY - Variable used in UE Editor, EditAnywhere: it can be edited by property windows
	*/
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;


	// Gameplay Ability System variables
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
