// Copyright (c) fivefingergames 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributesComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLOODANDSOUL_API UAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	/**
	 * @fn	UAttributesComponents::UAttributesComponents();
	 *
	 * @brief	Default constructor
	 */
	UAttributesComponent();

	/**
	 * @fn	virtual void UAttributesComponents::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	 *
	 * @brief	Tick component, will be called every frame.
	 *
	 * @param 		  	DeltaTime			The delta time.
	 * @param 		  	TickType			Type of the tick.
	 * @param [in,out]	ThisTickFunction	If non-null, this tick function.
	 */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Will be fired when the character dies. */
	UPROPERTY(BlueprintAssignable, Category = "Twitch Auth|Events")
	FOnDeath OnDeath;

	/**
	 * @fn	float UAttributesComponents::GetMaxStamina() const;
	 *
	 * @brief	Gets maximum stamina.
	 *
	 * @returns	Maximum stamina.
	 */
	int32 GetMaxStamina() const;

	/**
	 * @fn	float UAttributesComponents::GetStamina() const;
	 *
	 * @brief	Gets the current stamina.
	 *
	 * @returns	Current stamina.
	 */ 
	int32 GetStamina() const;

	/**
	 * @fn	void UAttributesComponent::IncreaseMaxStamina(float Amount);
	 *
	 * @brief	Adds to the max stamina.
	 *
	 * @param	Amount	Stamina to add.
	 */
	void IncreaseMaxStamina(int32 Amount);

	/**
	 * @fn	void UAttributesComponent::ReduceMaxStamina(float Amount);
	 *
	 * @brief	Removes from the max stamina.
	 *
	 * @param	Amount	Stamina to remove.
	 */
	void ReduceMaxStamina(int32 Amount);

	/**
	 * @fn	void UAttributesComponent::IncreaseStamina(float Amount);
	 *
	 * @brief	Adds to the current stamina.
	 *
	 * @param	Amount	Stamina to add.
	 */
	void IncreaseStamina(int32 Amount);

	/**
	 * @fn	void UAttributesComponent::ReduceStamina(float Amount);
	 *
	 * @brief	Removes from the current stamina.
	 *
	 * @param	Amount	Stamina to remove.
	 */
	void ReduceStamina(int32 Amount);

	/**
	 * @fn	float UAttributesComponents::GetMaxHealth() const;
	 *
	 * @brief	Gets maximum health.
	 *
	 * @returns	Maximum health.
	 */
	int32 GetMaxHealth() const;

	/**
	 * @fn	float UAttributesComponents::GetHealth() const;
	 *
	 * @brief	Gets current the health.
	 *
	 * @returns	Current health.
	 */
	int32 GetHealth() const;

	/**
	 * @fn	void UAttributesComponent::IncreaseMaxHealth(float Amount);
	 *
	 * @brief	Increases the max health.
	 *
	 * @param	Amount	Amount of health to add.
	 */
	void IncreaseMaxHealth(int32 Amount);

	/**
	 * @fn	void UAttributesComponent::ReduceMaxHealth(float Amount);
	 *
	 * @brief	Reduces the max health.
	 *
	 * @param	Amount	Amount of health to remove.
	 */
	void ReduceMaxHealth(int32 Amount);

	/**
	 * @fn	void UAttributesComponent::IncreaseHealth(float Amount);
	 *
	 * @brief	Increases the current health.
	 *
	 * @param	Amount	Amount of health to add.
	 */
	void IncreaseHealth(int32 Amount);

	/**
	 * @fn	void UAttributesComponent::ReduceHealth(float Amount);
	 *
	 * @brief	Reduces the current health.
	 *
	 * @param	Amount	Amount of health to remove.
	 */
	void ReduceHealth(int32 Amount);

	/**
	 * @fn	int32 UAttributesComponent::GetMaxSoul();
	 *
	 * @brief	Gets maximum soul
	 *
	 * @returns	The maximum soul.
	 */
	int32 GetMaxSoul();

	/**
	 * @fn	int32 UAttributesComponent::GetSoul();
	 *
	 * @brief	Gets the soul
	 *
	 * @returns	The soul.
	 */
	int32 GetSoul();

	/**
	 * @fn	void UAttributesComponent::IncreasSoul(int32 Amount);
	 *
	 * @brief	Increas soul
	 *
	 * @param	Amount	The amount.
	 */
	void IncreasSoul(int32 Amount);

	/**
	 * @fn	void UAttributesComponent::ReduceSoul(int32 Amount);
	 *
	 * @brief	Reduce soul
	 *
	 * @param	Amount	The amount.
	 */
	void ReduceSoul(int32 Amount);

	/**
	 * @fn	void UAttributesComponent::RegenerateStamina();
	 *
	 * @brief	Regenerates the stamina.
	 */
	void RegenerateStamina();

	/**
	 * @fn	void UAttributesComponent::StopStaminaRegeneration();
	 *
	 * @brief	Stops the currently running stamina regeneration.
	 */
	void StopStaminaRegeneration();

	/**
	 * @fn	bool UAttributesComponent::IsStaminaRegenerating() const;
	 *
	 * @brief	Query if stamina is currently regenerating.
	 *
	 * @returns	True if stamina is currently regenerating, false if not.
	 */
	bool IsStaminaRegenerating() const;


protected:

	/**
	 * @fn	virtual void UAttributesComponents::BeginPlay() override;
	 *
	 * @brief	Will be called when component is attached to a actor or when a actor spawns it's attached to.
	 */
	virtual void BeginPlay() override;

	/**
	 * @fn	void UAttributesComponent::OnStaminaRegenerationUpdate();
	 *
	 * @brief	Will be called on every stamina regeneration update.
	 */
	void OnStaminaRegenerationTick();


private:
		
	/** Maximum stamina. */
	UPROPERTY(EditAnywhere, Category = "Blood & Soul | Attributes | Stamina", meta = (AllowPrivateAccess = "true"))
	int32 MaxStamina;

	/** Current stamina. */
	UPROPERTY(EditAnywhere, Category = "Blood & Soul | Attributes | Stamina", meta = (AllowPrivateAccess = "true"))
	int32 Stamina;

	/** Cooldown before stamina regeneration starts. */
	UPROPERTY(EditAnywhere, Category = "Blood & Soul | Attributes | Stamina", meta = (AllowPrivateAccess = "true"))
	float StaminaRegenerationCooldown;

	/** Speed of the stamina regeneration. */
	UPROPERTY(EditAnywhere, Category = "Blood & Soul | Attributes | Stamina", meta = (AllowPrivateAccess = "true"))
	float StaminaRegenerationSpeed;

	/** Amount of stamina regenerated on every, regeneration update. */
	UPROPERTY(EditAnywhere, Category = "Blood & Soul | Attributes | Stamina", meta = (AllowPrivateAccess = "true"))
	int32 StaminaRegenerationAmount;

	/** Maximum health. */
	UPROPERTY(EditAnywhere, Category = "Blood & Soul | Attributes | Health", meta = (AllowPrivateAccess = "true"))
	int32 MaxHealth;

	/** Current health. */
	UPROPERTY(EditAnywhere, Category = "Blood & Soul | Attributes | Health", meta = (AllowPrivateAccess = "true"))
	int32 Health;

	/** Maximum soul. */
	UPROPERTY(EditAnywhere, Category = "Blood & Soul | Attributes | Health", meta = (AllowPrivateAccess = "true"))
	int32 MaxSoul;

	/** Current soul. */
	UPROPERTY(EditAnywhere, Category = "Blood & Soul | Attributes | Health", meta = (AllowPrivateAccess = "true"))
	int32 Soul;

	/** @brief	Stamina regeneration timer */
	FTimerHandle m_StaminaRegenerationTimer;
	bool m_IsStaminaRegenerating;
};
