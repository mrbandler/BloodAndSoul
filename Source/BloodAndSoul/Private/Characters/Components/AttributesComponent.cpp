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

float UAttributesComponent::GetMaxStamina() const
{
	return MaxStamina;
}

float UAttributesComponent::GetStamina() const
{
	return Stamina;
}

void UAttributesComponent::AddMaxStamina(float StaminaToAdd)
{
	MaxStamina += StaminaToAdd;
}

void UAttributesComponent::RemoveMaxStamina(float StaminaToRemove)
{
	MaxStamina = FMath::Clamp<float>(MaxStamina - StaminaToRemove, 0, MaxHealth);
}

void UAttributesComponent::AddStamina(float StaminaToAdd)
{
	Stamina = FMath::Clamp<float>(Stamina + StaminaToAdd, 0, MaxStamina);
}

void UAttributesComponent::RemoveStamina(float StaminaToRemove)
{
	Stamina = FMath::Clamp<float>(Stamina - StaminaToRemove, 0, MaxStamina);
}

float UAttributesComponent::GetMaxHealth() const
{
	return MaxHealth;
}

float UAttributesComponent::GetHealth() const
{
	return Health;
}

void UAttributesComponent::AddMaxHealth(float HealthToAdd)
{
	MaxHealth += HealthToAdd;
}

void UAttributesComponent::RemoveMaxHealth(float HealthToRemove)
{
	MaxHealth = FMath::Clamp<float>(MaxHealth - HealthToRemove, 0, MaxHealth);
}

void UAttributesComponent::AddHealth(float HealthToAdd)
{
	Health = FMath::Clamp<float>(Health + HealthToAdd, 0, MaxHealth);
}

void UAttributesComponent::RemoveHealth(float HealthToRemove)
{
	Health = FMath::Clamp<float>(Health - HealthToRemove, 0, Health);
}

void UAttributesComponent::RegenerateStamina()
{
	m_IsStaminaRegenerating = true;
	GetWorld()->GetTimerManager().SetTimer(m_StaminaRegenerationTimer, this, &UAttributesComponent::OnStaminaRegenerationUpdate, StaminaRegenerationSpeed, true, StaminaRegenerationCooldown);
}

void UAttributesComponent::OnStaminaRegenerationUpdate()
{
	AddStamina(StaminaRegenerationAmount);
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
