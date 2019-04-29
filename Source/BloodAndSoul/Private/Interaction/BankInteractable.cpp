// Copyright (c) fivefingergames 2019

#include "Interaction/BankInteractable.h"
#include "Items/Components/BankComponent.h"
#include "Items/Components/InventoryComponent.h"
#include "Characters/Player/PlayerCharacter.h"
#include "Characters/Components/AttributesComponent.h"

ABankInteractable::ABankInteractable() : AInteractable() 
{
	Bank = CreateDefaultSubobject<UBankComponent>(TEXT("Bank"));
}

int32 ABankInteractable::GetAvailableInventoryItems(EGearType Type) const
{
	int32 result = 0;

	UInventoryComponent* inventory = GetInteractor()->GetInventory();
	TArray<FGearItem*> gear = inventory->GetItems<FGearItem>();

	for (FGearItem* item : gear)
	{
		if (item->Type == Type)
		{
			result++;
		}
	}

	return result;
}

int32 ABankInteractable::GetAvailableBlood() const
{
	UAttributesComponent* attributes = GetInteractor()->GetAttributes();
	return attributes->GetHealth();
}

int32 ABankInteractable::GetMaxAvailableBlood() const
{
	UAttributesComponent* attributes = GetInteractor()->GetAttributes();
	return attributes->GetMaxHealth();
}

int32 ABankInteractable::GetAvailableSouls() const
{
	UAttributesComponent* attributes = GetInteractor()->GetAttributes();
	return attributes->GetSoul();
}

int32 ABankInteractable::GetDepositInterest(int32 Deposit, float InterestRate)
{
	return Bank->CalcInterests(Deposit, InterestRate);
}

void ABankInteractable::ConvertBlood(int32 Amount)
{
	UAttributesComponent* attributes = GetInteractor()->GetAttributes();
	UInventoryComponent* inventory = GetInteractor()->GetInventory();

	int32 amountWithFee = Amount + Bank->GetExchangeFee();
	TArray<FGearItem*> bloodVails = Bank->ConvertBlood(amountWithFee);

	attributes->ReduceHealth(Bank->GetExchangeFee());
	for (FGearItem* item : bloodVails)
	{
		inventory->AddItem(item);
		attributes->ReduceHealth(item->Amount);
	}
}

void ABankInteractable::Deposit(int32 Amount, EGearType Type)
{
	UAttributesComponent* attributes = GetInteractor()->GetAttributes();
	UInventoryComponent* inventory = GetInteractor()->GetInventory();
	TArray<FGearItem*> gear = inventory->GetItems<FGearItem>();
	
	TArray<FGearItem*> gearWithType;
	for (int i = gear.Num(); i >= 0; i--)
	{
		if (gear[i]->Type == Type)
		{
			gearWithType.Add(gear[i]);
		}
	}

	TArray<FGearItem*> toDeposit;
	for (int i = 0; i < Amount; i++)
	{
		toDeposit.Add(gearWithType[i]);
	}

	Bank->Deposit(toDeposit);
	switch (Type)
	{
		case EGearType::BloodVial:
			attributes->ReduceHealth(Bank->GetDepositFee());
		case EGearType::SoulShard:
			attributes->ReduceSoul(Bank->GetDepositFee());
	}
}

void ABankInteractable::Withdraw(int32 Amount, EGearType Type)
{
	UInventoryComponent* inventory = GetInteractor()->GetInventory();
	TArray<FGearItem*> withdrawnGear = Bank->Withdraw(Amount, Type);
	
	for (FGearItem* item : withdrawnGear)
	{
		if (inventory->AddItem(item) == false) 
		{
			break;
		}
	}
}

int32 ABankInteractable::GetDepositedBloodVials() const
{
	return Bank->GetDepositedBloodVialAmount();
}

int32 ABankInteractable::GetDepositedSoulShards() const
{
	return Bank->GetDepositedSoulShardAmount();
}
