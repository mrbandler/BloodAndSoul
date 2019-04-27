// Copyright (c) fivefingergames 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/DataTable.h"
#include "Items/Database/WeaponItem.h"
#include "BSGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BLOODANDSOUL_API ABSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	/**
	 * @fn	UDataTable* ABSGameModeBase::GetWeaponDB();
	 *
	 * @brief	Returns the complete weapon DB.
	 *
	 * @returns	Null if it fails, else the weapon database.
	 */
	UDataTable* GetWeaponDB() const;

	/**
	 * @fn	FWeaponItem ABSGameModeBase::GetWeaponFromDB(int32 WeaponId);
	 *
	 * @brief	Returns a weapon from database.
	 *
	 * @param	WeaponId	Identifier for the weapon.
	 *
	 * @returns	The weapon from database.
	 */
	FWeaponItem* GetWeaponFromDB(FName WeaponId) const;

private:

	/** Weapon DB. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blood & Soul | Items", meta = (AllowPrivateAccess = "true"))
	UDataTable* WeaponDB;

};
