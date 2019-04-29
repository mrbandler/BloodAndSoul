// Copyright (c) fivefingergames 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Items/Database/GearItem.h"
#include "BankComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLOODANDSOUL_API UBankComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	/**
	 * @fn	UBankComponent::UBankComponent();
	 *
	 * @brief	Default constructor.
	 */
	UBankComponent();

	/**
	 * @fn	virtual void UBankComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	 *
	 * @brief	Will be called every tick.
	 *
	 * @param 		  	DeltaTime			The delta time.
	 * @param 		  	TickType			Type of the tick.
	 * @param [in,out]	ThisTickFunction	If non-null, this tick function.
	 */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * @fn	int32 UBankComponent::GetExchangeFee() const;
	 *
	 * @brief	Returns exchange fee.
	 *
	 * @returns	Exchange fee.
	 */
	int32 GetExchangeFee() const;

	/**
	 * @fn	int32 UBankComponent::GetDepositFee() const;
	 *
	 * @brief	Gets deposit fee
	 *
	 * @returns	The deposit fee.
	 */
	int32 GetDepositFee() const;

	/**
	 * @fn	float UBankComponent::GetBloodInterestRate();
	 *
	 * @brief	Returns blood interest rate.
	 *
	 * @returns	Blood interest rate.
	 */
	float GetBloodInterestRate();

	/**
	 * @fn	float UBankComponent::GetSoulInterestRate();
	 *
	 * @brief	Returns soul interest rate.
	 *
	 * @returns	Soul interest rate.
	 */
	float GetSoulInterestRate();

	/**
	 * @fn	TArray<FGearItem*> UBankComponent::ConvertBlood(int32 Blood) const;
	 *
	 * @brief	Converts blood into blood veils.
	 *
	 * @param	Blood	Blood to convert.
	 *
	 * @returns	Null if it fails, else the blood converted.
	 */
	TArray<FGearItem*> ConvertBlood(int32 Blood);

	/**
	 * @fn	void UBankComponent::Deposit(TArray<FGearItem*> Items);
	 *
	 * @brief	Deposits gear item.
	 *
	 * @param [in,out]	Items	If non-null, the items.
	 */
	void Deposit(TArray<FGearItem*> Items);

	/**
	 * @fn	int32 UBankComponent::GetDepositedBloodVeilAmount() const;
	 *
	 * @brief	Returns deposited blood veil amount.
	 *
	 * @returns	Deposited blood veil amount.
	 */
	int32 GetDepositedBloodVialAmount() const;

	/**
	 * @fn	int32 UBankComponent::GetDespositedBloodAmount() const;
	 *
	 * @brief	Returns desposited blood amount.
	 *
	 * @returns	Desposited blood amount.
	 */
	int32 GetDespositedBloodAmount() const;

	/**
	 * @fn	int32 UBankComponent::GetDepositedSoulShardAmount() const;
	 *
	 * @brief	Returns deposited soul shard amount.
	 *
	 * @returns	Deposited soul shard amount.
	 */
	int32 GetDepositedSoulShardAmount() const;

	/**
	 * @fn	int32 UBankComponent::GetDespositedSoulAmount() const;
	 *
	 * @brief	Returns desposited soul amount.
	 *
	 * @returns	Desposited soul amount.
	 */
	int32 GetDespositedSoulAmount() const;

	/**
	 * @fn	TArray<FGearItem*> UBankComponent::Withdraw(int32 Amount);
	 *
	 * @brief	Withdraws items.
	 *
	 * @param	Amount	Amount.
	 *
	 * @returns	Null if it fails, else a TArray&lt;FGearItem*&gt;
	 */
	TArray<FGearItem*> Withdraw(int32 Amount, EGearType Type);

	/**
	 * @fn	int32 UBankComponent::CalcInterests(int32 DepositedAmount, int32 InterestRate);
	 *
	 * @brief	Calculates the interest.
	 *
	 * @param	DepositedAmount	Depsited amount.
	 * @param	InterestRate   	Interest rate.
	 *
	 * @returns	Calculated interest.
	 */
	int32 CalcInterests(int32 DepositedAmount, int32 InterestRate);

protected:

	/**
	 * @fn	virtual void UBankComponent::BeginPlay() override;
	 *
	 * @brief	Will be called when the owning actor spawns or the component is added to actor at runtime.
	 */
	virtual void BeginPlay() override;
		
private:

	/** Exchange fee for blood to blood veil conversion. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blood & Soul | Banking", meta = (AllowPrivateAccess = "true"))
	int32 ExchangeFee;

	/** Exchange fee for blood to blood veil conversion. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blood & Soul | Banking", meta = (AllowPrivateAccess = "true"))
	int32 DepositFee;

	/** Interest rate for blood vails. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blood & Soul | Banking", meta = (AllowPrivateAccess = "true"))
	float BloodInterestRate;

	/** Interest rate for soul shards. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blood & Soul | Banking", meta = (AllowPrivateAccess = "true"))
	float SoulInterestRate;

	/** Exchange fee for blood to blood veil conversion. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blood & Soul | Banking", meta = (AllowPrivateAccess = "true"))
	float InterestRateTickTime;

	/** @brief	Last blood interest. */
	int32 m_LastBloodInterest;

	/** @brief	Last soul interest. */
	int32 m_LastSoulInterest;

	/** @brief	The interest rate timer. */
	FTimerHandle m_InterestRateTimer;

	/** @brief	Bank account. */
	TArray<FGearItem*> m_BankAccount;

	/**
	 * @class	ABSGameModeBase*
	 *
	 * @brief	The game mode.
	 */
	class ABSGameModeBase* GetGameMode();

	/**
	 * @fn	void UBankComponent::SetupTimer();
	 *
	 * @brief	Sets up the timer.
	 */
	void SetupTimer();

	/**
	 * @fn	void UBankComponent::OnInterestRateTick();
	 *
	 * @brief	Executes the interest rate tick action.
	 */
	void OnInterestRateTick();

};
