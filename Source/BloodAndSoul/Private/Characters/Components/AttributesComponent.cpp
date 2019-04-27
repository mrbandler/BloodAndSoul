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

int UAttributesComponent::GetMaxStamina() const
{
	return MaxStamina;
}

int UAttributesComponent::GetStamina() const
{
	return Stamina;
}

void UAttributesComponent::IncreaseMaxStamina(int Amount)
{
	MaxStamina += Amount;
}

void UAttributesComponent::ReduceMaxStamina(int Amount)
{
	MaxStamina = FMath::Clamp<int>(MaxStamina - Amount, 0, MaxHealth);
}

void UAttributesComponent::IncreaseStamina(int Amount)
{
	Stamina = FMath::Clamp<int>(Stamina + Amount, 0, MaxStamina);
}

void UAttributesComponent::ReduceStamina(int Amount)
{
	Stamina = FMath::Clamp<int>(Stamina - Amount, 0, MaxStamina);
}

int UAttributesComponent::GetMaxHealth() const
{
	return MaxHealth;
}

int UAttributesComponent::GetHealth() const
{
	return Health;
}

void UAttributesComponent::IncreaseMaxHealth(int Amount)
{
	MaxHealth += Amount;
}

void UAttributesComponent::ReduceMaxHealth(int Amount)
{
	MaxHealth = FMath::Clamp<int>(MaxHealth - Amount, 0, MaxHealth);
}

void UAttributesComponent::IncreaseHealth(int HealthToAdd)
{
	Health = FMath::Clamp<int>(Health + HealthToAdd, 0, MaxHealth);
}

void UAttributesComponent::ReduceHealth(int32 HealthToRemove)
{
	Health = FMath::Clamp<int>(Health - HealthToRemove, 0, Health);
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
