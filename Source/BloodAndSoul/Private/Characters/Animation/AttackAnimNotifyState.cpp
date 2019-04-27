// Copyright (c) fivefingergames 2019

#include "Characters/Animation/AttackAnimNotifyState.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "Items/Gameplay/Weapon.h"
#include "Characters/Player/PlayerCharacter.h"

AWeapon* UAttackAnimNotifyState::GetAttackWeapon(ACharacter* AnimationCharacter)
{
	AWeapon* result = nullptr;

	if (AnimationCharacter->IsA<APlayerCharacter>() == true) 
	{
		APlayerCharacter* player = Cast<APlayerCharacter>(AnimationCharacter);
		result = player->GetEquippedWeapon();
	}
	
	//TODO: Branch for enemies.
	// 
	return result;
}

void UAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	m_AnimationCharacter = GetCharacterFromSkeletalMeshComponent(MeshComp);
	if (m_AnimationCharacter != nullptr)
	{
		if (AWeapon* weapon = GetAttackWeapon(m_AnimationCharacter))
		{
			weapon->AttackBegin();
		}
	}
}

void UAttackAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (m_AnimationCharacter != nullptr)
	{
		if (AWeapon* weapon = GetAttackWeapon(m_AnimationCharacter))
		{
			weapon->AttackTick();
		}
	}
}

void UAttackAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (m_AnimationCharacter != nullptr)
	{
		if (AWeapon* weapon = GetAttackWeapon(m_AnimationCharacter))
		{
			weapon->AttackEnd();
		}

		m_AnimationCharacter = nullptr;
	}
}

ACharacter* UAttackAnimNotifyState::GetCharacterFromSkeletalMeshComponent(USkeletalMeshComponent* MeshComp)
{
	ACharacter* result = nullptr;

	if (MeshComp != nullptr)
	{
		if (MeshComp->GetOwner()->IsA<ACharacter>() == true)
		{
			result = Cast<ACharacter>(MeshComp->GetOwner());
		}
	}

	return result;
}