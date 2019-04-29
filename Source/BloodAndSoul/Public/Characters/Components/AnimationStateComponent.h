// Copyright (c) fivefingergames 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AnimationStateComponent.generated.h"

USTRUCT(BlueprintType)
struct FCharacterAnimationState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	bool bJumping = false;

	UPROPERTY(BlueprintReadOnly)
	bool bHit = false;

	UPROPERTY(BlueprintReadOnly)
	bool bAttacking = false;

	UPROPERTY(BlueprintReadOnly)
	bool bDefending = false;

	UPROPERTY(BlueprintReadOnly)
	bool bDodging = false;

	UPROPERTY(BlueprintReadOnly)
	bool bDead = false;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLOODANDSOUL_API UAnimationStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	/**
	 * @fn	UAnimationStateComponent::UAnimationStateComponent();
	 *
	 * @brief	Default constructor.
	 */
	UAnimationStateComponent();

	/**
	 * @fn	virtual void UAnimationStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	 *
	 * @brief	Will be called every frame.
	 *
	 * @param 		  	DeltaTime			The delta time.
	 * @param 		  	TickType			Type of the tick.
	 * @param [in,out]	ThisTickFunction	If non-null, this tick function.
	 */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * @fn	FCharacterAnimationState UAnimationStateComponent::GetCharacterAnimationState();
	 *
	 * @brief	Gets character animation state
	 *
	 * @returns	The character animation state.
	 */
	UFUNCTION(BlueprintCallable, Category = "Soul & Vessel | Animation")
	FCharacterAnimationState GetCharacterAnimationState();

	/**
	 * @fn	virtual void UAnimationStateComponent::Jump();
	 *
	 * @brief	Sets the jumping flag inside the animation state.
	 */
	virtual void Jump();

	/**
	 * @fn	virtual void UAnimationStateComponent::Hit();
	 *
	 * @brief	Sets the hit flag inside the animation state.
	 */
	virtual void Hit();

	/**
	 * @fn	virtual void UAnimationStateComponent::Attacking();
	 *
	 * @brief	Sets the attacking flag inside the animation state.
	 */
	virtual void Attack();

	/**
	 * @fn	virtual void UAnimationStateComponent::Defend(bool IsDefending);
	 *
	 * @brief	Sets the defending flag inside the animation state.
	 *
	 * @param	IsDefending	True if is defending, false if not.
	 */
	virtual void Defend(bool IsDefending);

	/**
	 * @fn	virtual void UAnimationStateComponent::Dodging();
	 *
	 * @brief	Sets the dodging flag inside the animation state.
	 */
	virtual void Dodge();

	/**
	 * @fn	virtual void UAnimationStateComponent::Dead();
	 *
	 * @brief	Sets the dead flag inside the animation state.
	 */
	virtual void Die();

protected:

	/**
	 * @fn	virtual void UAnimationStateComponent::BeginPlay() override;
	 *
	 * @brief	Will be called when the owning actor spawns, or the component is added to actor on runtime.
	 */
	virtual void BeginPlay() override;

	/**
	 * @fn	void UAnimationStateComponent::StartJumpResetTimer();
	 *
	 * @brief	Starts the jump reset timer.
	 */
	void StartJumpResetTimer();

	/**
	 * @fn	void UAnimationStateComponent::StartAttackResetTimer();
	 *
	 * @brief	Starts the attack reset timer.
	 */
	void StartAttackResetTimer();

	/**
	 * @fn	void UAnimationStateComponent::StartHitResetTimer();
	 *
	 * @brief	Starts the hit reset timer.
	 */
	void StartHitResetTimer();

	/**
	 * @fn	void UAnimationStateComponent::StartDodgeResetTimer();
	 *
	 * @brief	Starts the dodge reset timer.
	 */
	void StartDodgeResetTimer();

private:

	/** Time to reset transition bools. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blood & Soul | Animation", meta = (AllowPrivateAccess = "true"))
	float ResetTime;

	/** @brief	State of the character animation. */
	FCharacterAnimationState m_CharacterAnimationState;
	
	/** @brief	Jump reset timer. */
	FTimerHandle m_JumpResetTimer;

	/** @brief	Attack reset timer. */
	FTimerHandle m_AttackResetTimer;

	/** @brief	Hit reset timer. */
	FTimerHandle m_HitResetTimer;

	/** @brief	Dodge reset timer. */
	FTimerHandle m_DodgeResetTimer;

	/**
	 * @fn	void UAnimationStateComponent::OnJumpReset();
	 *
	 * @brief	Executes the jump reset action.
	 */
	void OnJumpReset();

	/**
	 * @fn	void UAnimationStateComponent::OnAttackReset();
	 *
	 * @brief	Executes the attack reset action.
	 */
	void OnAttackReset();

	/**
	 * @fn	void UAnimationStateComponent::OnHitReset();
	 *
	 * @brief	Executes the hit reset action.
	 */
	void OnHitReset();

	/**
	 * @fn	void UAnimationStateComponent::OnDodgeReset();
	 *
	 * @brief	Executes the dodge reset action.
	 */
	void OnDodgeReset();

};
