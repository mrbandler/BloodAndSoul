// Copyright (c) fivefingergames 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributesComponent.generated.h"


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

	/**
	 * @fn	float UAttributesComponents::GetMaxStamina() const;
	 *
	 * @brief	Gets maximum stamina.
	 *
	 * @returns	Maximum stamina.
	 */
	float GetMaxStamina() const;

	/**
	 * @fn	float UAttributesComponents::GetStamina() const;
	 *
	 * @brief	Gets the current stamina.
	 *
	 * @returns	Current stamina.
	 */ 
	float GetStamina() const;

	/**
	 * @fn	void UAttributesComponents::AddMaxStamina(float StaminaToAdd);
	 *
	 * @brief	Adds to the max stamina.
	 *
	 * @param	StaminaToAdd	Stamina to add.
	 */
	void AddMaxStamina(float StaminaToAdd);

	/**
	 * @fn	void UAttributesComponents::RemoveMaxStamina(float StaminaToRemove);
	 *
	 * @brief	Removes from the max stamina.
	 *
	 * @param	StaminaToRemove	Stamina to remove.
	 */
	void RemoveMaxStamina(float StaminaToRemove);

	/**
	 * @fn	void UAttributesComponents::AddStamina(float StaminaToAdd);
	 *
	 * @brief	Adds to the current stamina.
	 *
	 * @param	StaminaToAdd	Stamina to add.
	 */
	void AddStamina(float StaminaToAdd);

	/**
	 * @fn	void UAttributesComponents::RemoveStamina(float StaminaToRemove);
	 *
	 * @brief	Removes from the current stamina.
	 *
	 * @param	StaminaToRemove	Stamina to remove.
	 */
	void RemoveStamina(float StaminaToRemove);

	/**
	 * @fn	float UAttributesComponents::GetMaxHealth() const;
	 *
	 * @brief	Gets maximum health.
	 *
	 * @returns	Maximum health.
	 */
	float GetMaxHealth() const;

	/**
	 * @fn	float UAttributesComponents::GetHealth() const;
	 *
	 * @brief	Gets current the health.
	 *
	 * @returns	Current health.
	 */
	float GetHealth() const;

	/**
	 * @fn	void UAttributesComponents::AddMaxHealth(float HealthToAdd);
	 *
	 * @brief	Adds to the max health.
	 *
	 * @param	HealthToAdd	Amount of health to add.
	 */
	void AddMaxHealth(float HealthToAdd);

	/**
	 * @fn	void UAttributesComponents::RemoveMaxHealth(float HealthToRemove);
	 *
	 * @brief	Removes from the max health.
	 *
	 * @param	HealthToRemove	Amount of health to remove.
	 */
	void RemoveMaxHealth(float HealthToRemove);

	/**
	 * @fn	void UAttributesComponents::AddHealth(float HealthToAdd);
	 *
	 * @brief	Adds to the current health.
	 *
	 * @param	HealthToAdd	Amount of health to add.
	 */
	void AddHealth(float HealthToAdd);

	/**
	 * @fn	void UAttributesComponents::RemoveHealth(float HealthToRemove);
	 *
	 * @brief	Removes from the current health.
	 *
	 * @param	HealthToRemove	Amount of health to remove.
	 */
	void RemoveHealth(float HealthToRemove);

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
	void OnStaminaRegenerationUpdate();


private:
		
	/** Maximum stamina. */
	UPROPERTY(EditAnywhere, Category = "Blood & Soul | Attributes | Stamina", meta = (AllowPrivateAccess = "true"))
	float MaxStamina;

	/** Current stamina. */
	UPROPERTY(EditAnywhere, Category = "Blood & Soul | Attributes | Stamina", meta = (AllowPrivateAccess = "true"))
	float Stamina;

	/** Cooldown before stamina regeneration starts. */
	UPROPERTY(EditAnywhere, Category = "Blood & Soul | Attributes | Stamina", meta = (AllowPrivateAccess = "true"))
	float StaminaRegenerationCooldown;

	/** Speed of the stamina regeneration. */
	UPROPERTY(EditAnywhere, Category = "Blood & Soul | Attributes | Stamina", meta = (AllowPrivateAccess = "true"))
	float StaminaRegenerationSpeed;

	/** Amount of stamina regenerated on every, regeneration update. */
	UPROPERTY(EditAnywhere, Category = "Blood & Soul | Attributes | Stamina", meta = (AllowPrivateAccess = "true"))
	float StaminaRegenerationAmount;

	/** Maximum health. */
	UPROPERTY(EditAnywhere, Category = "Blood & Soul | Attributes | Health", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

	/** Current health. */
	UPROPERTY(EditAnywhere, Category = "Blood & Soul | Attributes | Health", meta = (AllowPrivateAccess = "true"))
	float Health;

	/** @brief	Stamina regeneration timer */
	FTimerHandle m_StaminaRegenerationTimer;
	bool m_IsStaminaRegenerating;
};
