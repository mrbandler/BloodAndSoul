// Copyright (c) fivefingergames 2019

#include "Characters/Components/AttributesComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Math/UnrealMathUtility.h"

UAttributesComponent::UAttributesComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	MaxHealth = 100;
	Health = 100;

	MaxSoul = 100;
	Soul = 100;

	MaxStamina = 100;
	Stamina = 100;
	StaminaRegenerationCooldown = 1.f;
	StaminaRegenerationSpeed = 0.1f;
	StaminaRegenerationAmount = 2.f;

	m_IsStaminaRegenerating = false;
}

void UAttributesComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAttributesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

int32 UAttributesComponent::GetMaxStamina() const
{
	return MaxStamina;
}

int32 UAttributesComponent::GetStamina() const
{
	return Stamina;
}

void UAttributesComponent::IncreaseMaxStamina(int32 Amount)
{
	MaxStamina += Amount;
}

void UAttributesComponent::ReduceMaxStamina(int32 Amount)
{
	MaxStamina = FMath::Clamp<int>(MaxStamina - Amount, 0, MaxHealth);
}

void UAttributesComponent::IncreaseStamina(int32 Amount)
{
	Stamina = FMath::Clamp<int>(Stamina + Amount, 0, MaxStamina);
}

void UAttributesComponent::ReduceStamina(int32 Amount)
{
	Stamina = FMath::Clamp<int>(Stamina - Amount, 0, MaxStamina);
}

int32 UAttributesComponent::GetMaxHealth() const
{
	return MaxHealth;
}

int32 UAttributesComponent::GetHealth() const
{
	return Health;
}

void UAttributesComponent::IncreaseMaxHealth(int32 Amount)
{
	MaxHealth += Amount;
}

void UAttributesComponent::ReduceMaxHealth(int32 Amount)
{
	MaxHealth = FMath::Clamp<int>(MaxHealth - Amount, 0, MaxHealth);
}

void UAttributesComponent::IncreaseHealth(int32 Amount)
{
	Health = FMath::Clamp<int>(Health + Amount, 0, MaxHealth);
}

void UAttributesComponent::ReduceHealth(int32 Amount)
{
	Health = FMath::Clamp<int>(Health - Amount, 0, Health);
	if (Health <= 0)
	{
		OnDeath.Broadcast();
	}
}

int32 UAttributesComponent::GetMaxSoul()
{
	return MaxSoul;
}

int32 UAttributesComponent::GetSoul()
{
	return Soul;
}

void UAttributesComponent::ReduceSoul(int32 Amount)
{
	Soul = FMath::Clamp<int>(Soul + Amount, 0, MaxSoul);
}

void UAttributesComponent::IncreasSoul(int32 Amount)
{
	Soul = FMath::Clamp<int>(Soul - Amount, 0, MaxSoul);
	if (Soul <= 0)
	{
		OnDeath.Broadcast();
	}
}

void UAttributesComponent::RegenerateStamina()
{
	m_IsStaminaRegenerating = true;
	GetWorld()->GetTimerManager().SetTimer(m_StaminaRegenerationTimer, this, &UAttributesComponent::OnStaminaRegenerationTick, StaminaRegenerationSpeed, true, StaminaRegenerationCooldown);
}

void UAttributesComponent::OnStaminaRegenerationTick()
{
	IncreaseStamina(StaminaRegenerationAmount);
	if (GetStamina() == GetMaxStamina())
	{
		StopStaminaRegeneration();
	}
}

void UAttributesComponent::StopStaminaRegeneration()
{
	m_IsStaminaRegenerating = false;
	GetWorld()->GetTimerManager().ClearTimer(m_StaminaRegenerationTimer);
}

bool UAttributesComponent::IsStaminaRegenerating() const
{
	return m_IsStaminaRegenerating;
}
