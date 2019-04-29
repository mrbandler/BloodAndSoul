// Copyright (c) fivefingergames 2019

#include "AnimationStateComponent.h"
#include "GameFramework/Actor.h"

UAnimationStateComponent::UAnimationStateComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	ResetTime = 0.2f;
}

void UAnimationStateComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAnimationStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FCharacterAnimationState UAnimationStateComponent::GetCharacterAnimationState()
{
	return m_CharacterAnimationState;
}

void UAnimationStateComponent::Jump()
{
	m_CharacterAnimationState.bJumping = true;
	StartJumpResetTimer();
}

void UAnimationStateComponent::Hit()
{
	m_CharacterAnimationState.bHit = true;
	StartHitResetTimer();
}

void UAnimationStateComponent::Attack()
{
	m_CharacterAnimationState.bAttacking = true;
	StartAttackResetTimer();
}

void UAnimationStateComponent::Defend(bool IsDefending)
{
	m_CharacterAnimationState.bDefending = IsDefending;
}

void UAnimationStateComponent::Dodge()
{
	m_CharacterAnimationState.bDodging = true;
	StartDodgeResetTimer();
}

void UAnimationStateComponent::Die()
{
	m_CharacterAnimationState.bDead = true;
}
void UAnimationStateComponent::StartJumpResetTimer()
{
	AActor* owner = GetOwner();
	if (owner != nullptr)
	{
		owner->GetWorldTimerManager().SetTimer(m_JumpResetTimer, this, &UAnimationStateComponent::OnJumpReset, ResetTime, false);
	}
}

void UAnimationStateComponent::StartAttackResetTimer()
{
	AActor* owner = GetOwner();
	if (owner != nullptr)
	{
		owner->GetWorldTimerManager().SetTimer(m_AttackResetTimer, this, &UAnimationStateComponent::OnAttackReset, ResetTime, false);
	}
}

void UAnimationStateComponent::StartHitResetTimer()
{
	AActor* owner = GetOwner();
	if (owner != nullptr)
	{
		owner->GetWorldTimerManager().SetTimer(m_HitResetTimer, this, &UAnimationStateComponent::OnHitReset, ResetTime, false);
	}
}

void UAnimationStateComponent::StartDodgeResetTimer()
{
	AActor* owner = GetOwner();
	if (owner != nullptr)
	{
		owner->GetWorldTimerManager().SetTimer(m_DodgeResetTimer, this, &UAnimationStateComponent::OnDodgeReset, ResetTime, false);
	}
}

void UAnimationStateComponent::OnJumpReset()
{
	m_CharacterAnimationState.bJumping = false;
}

void UAnimationStateComponent::OnAttackReset()
{
	m_CharacterAnimationState.bAttacking = false;
}

void UAnimationStateComponent::OnHitReset()
{
	m_CharacterAnimationState.bHit = false;
}

void UAnimationStateComponent::OnDodgeReset()
{
	m_CharacterAnimationState.bDodging = false;
}