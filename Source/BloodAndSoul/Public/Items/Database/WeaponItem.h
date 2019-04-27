#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Items/Gameplay/Weapon.h"
#include "Items/Database/Item.h"
#include "WeaponItem.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8 
{
	Sword,
	Axe,
	Hammer,
	Club
};

USTRUCT(BlueprintType)
struct FWeaponItem : public FItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AttackStaminaCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool BloodSteal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "BloodSteal"))
	int32 BloodStealAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "BloodSteal"))
	int32 BloodStealMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SoulSteal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "SoulSteal"))
	int32 SoulStealAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "SoulSteal"))
	int32 SoulStealMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWeapon> WeaponToEquip;

};