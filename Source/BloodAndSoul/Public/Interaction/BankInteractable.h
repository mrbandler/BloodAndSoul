// Copyright (c) fivefingergames 2019

#pragma once

#include "CoreMinimal.h"
#include "Interaction/Interactable.h"
#include "Items/Database/GearItem.h"
#include "BankInteractable.generated.h"

/**
 * 
 */
UCLASS()
class BLOODANDSOUL_API ABankInteractable : public AInteractable
{
	GENERATED_BODY()

public:
	ABankInteractable();

	/**
	 * @fn	int32 ABankInteractable::GetAvailableInventoryItems(EGearType Type) const;
	 *
	 * @brief	Returns available items inventory by a given type.
	 *
	 * @param	Type	Gear type.
	 *
	 * @returns	Available items in inventory.
	 */
	UFUNCTION(BlueprintCallable, Category = "Blood & Soul | Banking")
	int32 GetAvailableInventoryItems(EGearType Type) const;

	/**
	 * @fn	int32 ABankInteractable::GetAvailableBlood() const;
	 *
	 * @brief	Return available blood.
	 *
	 * @returns	Available blood.
	 */
	UFUNCTION(BlueprintPure, Category = "Blood & Soul | Banking")
	int32 GetAvailableBlood() const;

	/**
	 * @fn	int32 ABankInteractable::GetMaxAvailableBlood() const;
	 *
	 * @brief	Gets maximum available blood
	 *
	 * @returns	The maximum available blood.
	 */
	UFUNCTION(BlueprintPure, Category = "Blood & Soul | Banking")
	int32 GetMaxAvailableBlood() const;

	/**
	 * @fn	int32 ABankInteractable::GetAvailableSouls() const;
	 *
	 * @brief	Return available souls.
	 *
	 * @returns	Available souls.
	 */
	UFUNCTION(BlueprintPure, Category = "Blood & Soul | Banking")
	int32 GetAvailableSouls() const;

	/**
	 * @fn	int32 ABankInteractable::GetDepositedBloodVials() const;
	 *
	 * @brief	Gets deposited blood vials
	 *
	 * @returns	The deposited blood vials.
	 */
	UFUNCTION(BlueprintCallable, Category = "Blood & Soul | Banking")
	int32 GetDepositedBloodVials() const;

	/**
	 * @fn	int32 ABankInteractable::GetDepositedSoulShards() const;
	 *
	 * @brief	Gets deposited soul shards
	 *
	 * @returns	The deposited soul shards.
	 */
	UFUNCTION(BlueprintCallable, Category = "Blood & Soul | Banking")
	int32 GetDepositedSoulShards() const;

	/**
	 * @fn	int32 ABankInteractable::GetDepositInterest(int32 Deposit, float InterestRate);
	 *
	 * @brief	Returns deposit interest.
	 *
	 * @param	Deposit			Deposit.
	 * @param	InterestRate	Interest rate.
	 *
	 * @returns	Deposit interest.
	 */
	UFUNCTION(BlueprintCallable, Category = "Blood & Soul | Banking")
	int32 GetDepositInterest(int32 Deposit, float InterestRate);

	/**
	 * @fn	void ABankInteractable::ConvertBlood(int32 Amount);
	 *
	 * @brief	Converts blood.
	 *
	 * @param	Amount	The amount.
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "Blood & Soul | Banking")
	void ConvertBlood(int32 Amount);

	/**
	 * @fn	void ABankInteractable::Deposit(TArray<FGearItem*> Items);
	 *
	 * @brief	Deposits the given items.
	 *
	 * @param [in,out]	Items	If non-null, the items.
	 */
	UFUNCTION(BlueprintCallable, Category = "Blood & Soul | Banking")
	void Deposit(int32 Amount, EGearType Type);

	/**
	 * @fn	void ABankInteractable::Withdraw(int32 Amount, EGearType Type);
	 *
	 * @brief	Withdraws.
	 *
	 * @param	Amount	The amount.
	 * @param	Type  	The type.
	 */
	UFUNCTION(BlueprintCallable, Category = "Blood & Soul | Banking")
	void Withdraw(int32 Amount, EGearType Type);

private:

	/** Bank component. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBankComponent* Bank;

};
