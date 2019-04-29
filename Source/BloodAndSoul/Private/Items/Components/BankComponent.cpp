// Copyright (c) fivefingergames 2019

#include "BankComponent.h"
#include "GameModes/BSGameModeBase.h"
#include "Items/Database/DBConstants.h"
#include "Items/Database/GearItem.h"
#include "GameFramework/Actor.h"
#include "Public/TimerManager.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

UBankComponent::UBankComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBankComponent::BeginPlay()
{
	Super::BeginPlay();

	m_LastBloodInterest = 0;
	m_LastSoulInterest = 0;
	SetupTimer();
}

void UBankComponent::SetupTimer()
{
	AActor* owner = GetOwner();
	if (owner != nullptr)
	{
		owner->GetWorldTimerManager().SetTimer(m_InterestRateTimer, this, &UBankComponent::OnInterestRateTick, InterestRateTickTime, true, InterestRateTickTime);
	}
}

void UBankComponent::OnInterestRateTick()
{
	ABSGameModeBase* gameMode = GetGameMode();
	int32 depositedBlood = GetDespositedBloodAmount();
	int32 depositedSouls = GetDespositedSoulAmount();

	if (depositedBlood != 0) 
	{
		int32 bloodInterest = m_LastBloodInterest + CalcInterests(depositedBlood, BloodInterestRate);
		if (bloodInterest >= 5) 
		{
			FGearItem* bloodVial = gameMode->GetGearFromDB(UDBConstants::BloodVial5);
			m_BankAccount.Add(bloodVial);
			m_LastBloodInterest = 0;
		}

		if (bloodInterest >= 10)
		{
			FGearItem* bloodVial = gameMode->GetGearFromDB(UDBConstants::BloodVial10);
			m_BankAccount.Add(bloodVial);
			m_LastBloodInterest = 0;
		}
	}

	if (depositedSouls != 0)
	{
		int32 soulInterest = m_LastSoulInterest + CalcInterests(depositedSouls, BloodInterestRate);
		if (soulInterest >= 5)
		{
			FGearItem* soulShard = gameMode->GetGearFromDB(UDBConstants::SoulShard5);
			m_BankAccount.Add(soulShard);
			m_LastSoulInterest = 0;
		}

		if (soulInterest >= 10)
		{
			FGearItem* soulShard = gameMode->GetGearFromDB(UDBConstants::SoulShard10);
			m_BankAccount.Add(soulShard);
			m_LastSoulInterest = 0;
		}
	}
}

void UBankComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

int32 UBankComponent::CalcInterests(int32 DepositedAmount, int32 InterestRate)
{
	return FMath::FloorToInt((DepositedAmount * InterestRate * InterestRateTickTime) / (100 * InterestRateTickTime));
}

int32 UBankComponent::GetExchangeFee() const
{
	return ExchangeFee;
}

int32 UBankComponent::GetDepositFee() const
{
	return DepositFee;
}

float UBankComponent::GetBloodInterestRate()
{
	return BloodInterestRate;
}

float UBankComponent::GetSoulInterestRate()
{
	return SoulInterestRate;
}

ABSGameModeBase* UBankComponent::GetGameMode()
{
	return Cast<ABSGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

TArray<FGearItem*> UBankComponent::ConvertBlood(int32 Blood)
{
	TArray<FGearItem*> result;
	ABSGameModeBase* gameMode = GetGameMode();
	
	int32 bloodToConvert = Blood - DepositFee;
	
	int32 mod10 = bloodToConvert % 10;
	int32 mod5 = mod10 % 5;
	if (mod5 != 0) 
	{
		bloodToConvert -= mod5;
	}

	int32 vial10Count = FMath::FloorToInt(bloodToConvert / 10);
	for (int32 i = 0; i < vial10Count; i++) 
	{
		FGearItem* bloodVial = gameMode->GetGearFromDB(UDBConstants::BloodVial10);
		result.Add(bloodVial);
	}

	if (mod10 != 0) 
	{
		int32 vial5Count = FMath::FloorToInt(mod10 / 5);
		for (int32 i = 0; i < vial5Count; i++)
		{
			FGearItem* bloodVial = gameMode->GetGearFromDB(UDBConstants::BloodVial5);
			result.Add(bloodVial);
		}
	}

	return result;
}

void UBankComponent::Deposit(TArray<FGearItem*> Items)
{
	for (FGearItem* item : Items)
	{
		m_BankAccount.Add(item);
	}
}

int32 UBankComponent::GetDepositedBloodVialAmount() const
{
	int32 result = 0;
	for (FGearItem* item : m_BankAccount) 
	{
		if (item->Type == EGearType::BloodVial)
		{
			result++;
		}
	}

	return result;
}

int32 UBankComponent::GetDespositedBloodAmount() const
{
	int32 result = 0;
	for (FGearItem* item : m_BankAccount)
	{
		if (item->Type == EGearType::BloodVial)
		{
			result += item->Amount;
		}
	}

	return result;
}

int32 UBankComponent::GetDepositedSoulShardAmount() const
{
	int32 result = 0;
	for (FGearItem* item : m_BankAccount)
	{
		if (item->Type == EGearType::SoulShard)
		{
			result++;
		}
	}

	return result;
}

int32 UBankComponent::GetDespositedSoulAmount() const
{
	int32 result = 0;
	for (FGearItem* item : m_BankAccount)
	{
		if (item->Type == EGearType::SoulShard)
		{
			result += item->Amount;
		}
	}

	return result;
}

TArray<FGearItem*> UBankComponent::Withdraw(int32 Amount, EGearType Type)
{
	TArray<FGearItem*> result;

	int32 depositedAmount = 0;
	switch (Type) 
	{
		case EGearType::BloodVial:
			depositedAmount = GetDepositedBloodVialAmount();
		case EGearType::SoulShard:
			depositedAmount = GetDepositedSoulShardAmount();
	}

	if (depositedAmount <= Amount) 
	{
		int32 deposited = 0;
		for(int32 i = m_BankAccount.Num(); i >= 0; i--)
		{
			if (deposited == Amount)
			{
				break;
			}			

			FGearItem* item = m_BankAccount[i];
			if (item->Type == Type) 
			{
				result.Add(item);
				m_BankAccount.RemoveAt(i);
				deposited++;
			}
		}
	}

	return result;
}

