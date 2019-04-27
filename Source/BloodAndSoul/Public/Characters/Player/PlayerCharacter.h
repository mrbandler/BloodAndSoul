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
	// Sets default values for this character's properties
	APlayerCharacter();

	/** Returns spring arm component. **/
	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
	
	/** Returns camera component. **/
	FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }

protected:

	/** Camera spring arm used for positioning the camera behind the character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blood & Soul | Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	/** Camera. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blood & Soul | Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blood & Soul | Attributes", meta = (AllowPrivateAccess = "true"))
	class UAttributesComponent* Attributes;

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
	float SprintStaminaReduction;

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

private:

	void SetupDefaults();
	void SetupSceneComponents();
	void SetupActorComponents();

};
