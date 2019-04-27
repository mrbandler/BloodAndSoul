// Copyright (c) fivefingergames 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class BLOODANDSOUL_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	/**
	 * @fn	APlayerCharacter::APlayerCharacter();
	 *
	 * @brief	Default constructor.
	 */
	APlayerCharacter();

	/**
	 * @fn	AWeapon* APlayerCharacter::GetEquippedWeapon() const void Attack();
	 *
	 * @brief	Returns the currently equipped weapon.
	 *
	 * @returns	Null if it fails, else the equipped weapon.
	 */
	class AWeapon* GetEquippedWeapon() const;

protected:

	/** Camera spring arm used for positioning the camera behind the character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blood & Soul | Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	/** Camera. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blood & Soul | Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	/** Visible weapon. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blood & Soul | Combat", meta = (AllowPrivateAccess = "true"))
	class UChildActorComponent* Weapon;

	/** Attributes. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blood & Soul | Attributes", meta = (AllowPrivateAccess = "true"))
	class UAttributesComponent* Attributes;

	/** Inventory. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blood & Soul | Inventory", meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* Inventory;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blood & Soul | Camera", meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blood & Soul | Camera", meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;

	/** Walk speed. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blood & Soul | Movement", meta = (AllowPrivateAccess = "true"))
	float WalkSpeed;

	/** Sprint speed. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blood & Soul | Movement")
	float SprintSpeed;

	/** Sprint speed. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blood & Soul | Movement")
	int32 SprintStaminaReduction;

	/**
	 * @fn	virtual void APlayerCharacter::BeginPlay() override;
	 *
	 * @brief	Will be called when the character spawns.
	 */
	virtual void BeginPlay() override;

	/**
	 * @fn	virtual void APlayerCharacter::Tick(float DeltaTime) override;
	 *
	 * @brief	Will be called every frame.
	 *
	 * @param	DeltaTime	The delta time.
	 */
	virtual void Tick(float DeltaTime) override;

	/**
	 * @fn	virtual void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	 *
	 * @brief	Sets up the player input.
	 *
	 * @param [in,out]	PlayerInputComponent	If non-null, the player input component.
	 */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**
	 * @fn	void APlayerCharacter::MoveForward(float Value);
	 *
	 * @brief	Called for forwards/backward input.
	 *
	 * @param	Value	Axis value from the input.
	 */
	void MoveForward(float Value);

	/**
	 * @fn	void APlayerCharacter::MoveRight(float Value);
	 *
	 * @brief	Called for side to side input.
	 *
	 * @param	Value	Axis value from the input.
	 */
	void MoveRight(float Value);

	/**
	 * @fn	void APlayerCharacter::TurnAtRate(float Rate);
	 *
	 * @brief	Called via input to turn at a given rate.
	 *
	 * @param	Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate.
	 */
	void TurnAtRate(float Rate);

	/**
	 * @fn	void APlayerCharacter::LookUpAtRate(float Rate);
	 *
	 * @brief	Called via input to turn look up/down at a given rate.
	 *
	 * @param	Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate.
	 */
	void LookUpAtRate(float Rate);

	/**
	 * @fn	void APlayerCharacter::Sprint();
	 *
	 * @brief	Starts a sprint.
	 */
	void Sprint();

	/**
	 * @fn	void APlayerCharacter::StopSprinting();
	 *
	 * @brief	Stops a sprint
	 */
	void StopSprinting();

	/**
	 * @fn	void APlayerCharacter::EquipWeapon(struct FWeaponItem* WeaponItem);
	 *
	 * @brief	Equips the weapon for a given weapon item.
	 *
	 * @param [in,out]	WeaponItem	If non-null, the weapon item.
	 */
	void EquipWeapon(struct FWeaponItem* WeaponItem);

	/**
	 * @fn	void APlayerCharacter::Attack();
	 *
	 * @brief	Starts 
	 * 			an attack.
	 */
	void Attack();

	/**
	 * @fn	virtual float APlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
	 *
	 * @brief	Will be called when this character takes damage.
	 *
	 * @param 		  	DamageAmount   	The damage amount.
	 * @param 		  	DamageEvent	   	The damage event.
	 * @param [in,out]	EventInstigator	If non-null, the event instigator.
	 * @param [in,out]	DamageCauser   	If non-null, the damage causer.
	 *
	 * @returns	Damage taken.
	 */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:

	/**
	 * @fn	void APlayerCharacter::SetupDefaults();
	 *
	 * @brief	Sets up the default values.
	 */
	void SetupDefaults();

	/**
	 * @fn	void APlayerCharacter::SetupSceneComponents();
	 *
	 * @brief	Sets up the scene components.
	 */
	void SetupSceneComponents();

	/**
	 * @fn	void APlayerCharacter::SetupActorComponents();
	 *
	 * @brief	Sets up the actor components.
	 */
	void SetupActorComponents();

};
