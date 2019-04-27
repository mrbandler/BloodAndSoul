#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Items/Database/Item.h"
#include "GearItem.generated.h"

UENUM(BlueprintType)
enum class EGearType : uint8 
{
	BloodVeil,
	SoulShard
};

USTRUCT(BlueprintType)
struct FGearItem : public FItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGearType Type;

};