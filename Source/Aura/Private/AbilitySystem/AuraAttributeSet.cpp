// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAttributeSet.h"

// For DOREPLIFETIME_CONDITION_NOTIFY
#include "Net/UnrealNetwork.h"								

UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitMana(50.f);
	InitMaxMana(50.f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// In this section we register variables for replication
	// COND_None: It registers health to be replicated anytime it changes, without any conditions
	// REPNOTIFY_Always: if the value is set on the server, replicate it and update it in clients (OnChanged only replicated it when it changes from the local value)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	// It requires the type of the attribute set, the current attribute and the old value
	// When we set up the RepNotify for a replicated attribute, we have to inform the Ability System of that change
	// A value came from the server and changed, and the Ability System will check if it needs to roll back
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}


//#define CREATE_ATTRIBUTE(ATTR_NAME) \
// \
//	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_#ATTR_NAME, Category = "Vital Attributes")	\
//		FGameplayAttributeData ATTR_NAME;	\
//	UFUNCTION()	\
//		void OnRep_#ATTR_NAME(const FGameplayAttributeData& Old#ATTR_NAME) const;	\




//#define GAMEPLAYATTRIBUTE_REPNOTIFY(ClassName, PropertyName, OldValue) \
//{ \
//	static FProperty* ThisProperty = FindFieldChecked<FProperty>(ClassName::StaticClass(), GET_MEMBER_NAME_CHECKED(ClassName, PropertyName)); \
//	GetOwningAbilitySystemComponentChecked()->SetBaseAttributeValueFromReplication(FGameplayAttribute(ThisProperty), PropertyName, OldValue); \
//}

/*
// Mana Attributes
	

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;

	// RepNotify can have 0 or 1 argument, which is the type of the replicated variable
	// You will automatically get the previous value in RepNotifies, it is an inherent quality of RepNotifies
	

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

};


/* We can use a define to not repeat creating attribute data
*
#define REGISTER_DECO(DECO_NAME)  {#DECO_NAME, new CBTDecoratorFactory<CBTDeco##DECO_NAME>()},
std::map<std::string_view, CBTParser::IBTDecoratorFactory*> CBTParser::decorator_types{
	#include "bt_decorator_registration.h"
};
#undef REGISTER_DECO




*/