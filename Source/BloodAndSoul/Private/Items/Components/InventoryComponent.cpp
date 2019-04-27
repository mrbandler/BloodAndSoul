// Copyright (c) fivefingergames 2019

#include "Items/Components/InventoryComponent.h"
#include "Items/Database/WeaponItem.h"
#include "Items/Database/GearItem.h"
#include "Math/UnrealMathUtility.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventoryComponent::AddSlots(int Amount)
{
	MaxSlots += Amount;
}

void UInventoryComponent::RemoveSlots(int Amount)
{
	MaxSlots = FMath::Clamp<int>(MaxSlots - Amount, 0, MaxSlots);
}

bool UInventoryComponent::AddItem(FItem* Item)
{
	bool result = false;
	if (m_Items.Num() + 1 < MaxSlots) 
	{
		m_Items.Add(Item);
		result = true;
	}
	
	return result;
}

void UInventoryComponent::RemoveItem(FItem* Item)
{
	m_Items.RemoveSingle(Item);
}

void UInventoryComponent::RemoveItem(FName ItemId)
{
	for (FItem* item : m_Items)
	{
		if (item->Id == ItemId) 
		{
			RemoveItem(item);
			break;
		}
	}
}

