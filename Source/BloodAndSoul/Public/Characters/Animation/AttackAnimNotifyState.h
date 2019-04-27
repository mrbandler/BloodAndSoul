// Copyright (c) fivefingergames 2019

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AttackAnimNotifyState.generated.h"

// Forward declartions.
class ACharacter;
class AWeapon;

/**
 * 
 */
UCLASS()
class BLOODANDSOUL_API UAttackAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
protected:

	/**
	 * @fn	virtual AWeapon* UAttackAnimNotifyState::GetAttackWeapon(ACharacter* AnimationCharacter);
	 *
	 * @brief	Returns the attack weapon used for the animation.
	 *
	 * @param [in,out]	AnimationCharacter	If non-null, the animation character.
	 *
	 * @returns	Null if it fails, else the attack weapon.
	 */

	virtual AWeapon* GetAttackWeapon(ACharacter* AnimationCharacter);

	/**
	 * @fn  virtual void UAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
	 *
	 * @brief   Will be called when the notify state begins.
	 *
	 * @param [in,out]  MeshComp        If non-null, the mesh component.
	 * @param [in,out]  Animation       If non-null, the animation.
	 * @param           TotalDuration   Duration of the total.
	 */
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

	/**
	 * @fn	virtual void UAttackAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	 *
	 * @brief	Will be called for every tick the notify state runs.
	 *
	 * @param [in,out]	MeshComp	  	If non-null, the mesh component.
	 * @param [in,out]	Animation	  	If non-null, the animation.
	 * @param 		  	FrameDeltaTime	The frame delta time.
	 */

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;

	/**
	 * @fn	virtual void UAttackAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	 *
	 * @brief	Will be called when the notify state ends.
	 *
	 * @param [in,out]	MeshComp 	If non-null, the mesh component.
	 * @param [in,out]	Animation	If non-null, the animation.
	 */
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:

	/** Character used for the animation. */
	ACharacter* m_AnimationCharacter;

	/**
	 * @fn	ACharacter* UAttackAnimNotifyState::GetCharacterFromSkeletalMeshComponent(USkeletalMeshComponent* MeshComp);
	 *
	 * @brief	Returns the animation character from a given skeletal mesh component.
	 *
	 * @param [in,out]	MeshComp	If non-null, the mesh component.
	 *
	 * @returns	Null if it fails, else the player character from skeletal mesh component.
	 */
	ACharacter* GetCharacterFromSkeletalMeshComponent(USkeletalMeshComponent* MeshComp);

};
