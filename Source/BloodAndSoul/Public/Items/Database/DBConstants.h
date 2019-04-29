// Copyright (c) fivefingergames 2019

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DBConstants.generated.h"

/**
 * 
 */
UCLASS()
class BLOODANDSOUL_API UDBConstants : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	static const FName BloodVialEmpty;
	static const FName BloodVial5;
	static const FName BloodVial10;

	static const FName SoulShardEmpty;
	static const FName SoulShard5;
	static const FName SoulShard10;

};
