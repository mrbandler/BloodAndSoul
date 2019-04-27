// Copyright (c) fivefingergames 2019


#include "GameModes/BSGameModeBase.h"

UDataTable* ABSGameModeBase::GetWeaponDB() const
{
	return WeaponDB;
}

FWeaponItem* ABSGameModeBase::GetWeaponFromDB(FName WeaponId) const
{
	return WeaponDB->FindRow<FWeaponItem>(WeaponId, "");
}