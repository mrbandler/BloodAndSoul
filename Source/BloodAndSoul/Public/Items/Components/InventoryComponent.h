// Copyright (c) fivefingergames 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/Database/Item.h"
#include "InventoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLOODANDSOUL_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	/**
	 * @fn	UInventoryComponent::UInventoryComponent();
	 *
	 * @brief	Default constructor
	 */
	UInventoryComponent();

	/**
	 * @fn	virtual void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	 *
	 * @brief	Will be called on every frame.
	 *
	 * @param 		  	DeltaTime			The delta time.
	 * @param 		  	TickType			Type of the tick.
	 * @param [in,out]	ThisTickFunction	If non-null, this tick function.
	 */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * @fn	void UInventoryComponent::AddSlots(int Amount, ESlotType SlotType);
	 *
	 * @brief	Adds slots.
	 *
	 * @param	Amount  	Amount of slots to add.
	 */
	void AddSlots(int Amount);

	/**
	 * @fn	void UInventoryComponent::RemoveSlots(int Amount);
	 *
	 * @brief	Removes slots.
	 *
	 * @param	Amount	Amount of slots to add.
	 */
	void RemoveSlots(int Amount);

	/**
	 * @fn	void UInventoryComponent::AddItem(FItem* Item);
	 *
	 * @brief	Adds an item.
	 *
	 * @param [in,out]	Item	If non-null, the item.
	 */
	bool AddItem(FItem* Item);

	/**
	 * @fn	void UInventoryComponent::RemoveItem(FItem* Item);
	 *
	 * @brief	Removes a item by a given item.
	 *
	 * @param [in,out]	Item	If non-null, the item.
	 */
	void RemoveItem(FItem* Item);

	/**
	 * @fn	void UInventoryComponent::RemoveItem(FName ItemId);
	 *
	 * @brief	Removes a item by a given item ID.
	 *
	 * @param	ItemId	Identifier for the item.
	 */
	void RemoveItem(FName ItemId);

	/**
	 * @fn	template<typename T> T* UInventoryComponent::GetItem(FName ItemId) const
	 *
	 * @brief	Gets an item.
	 *
	 * @tparam	T	Generic type parameter.
	 * @param	ItemId	Identifier for the item.
	 *
	 * @returns	Null if it fails, else the item.
	 */
	template<typename T>
	T* GetItem(FName ItemId) const
	{
		T* result = nullptr;
		
		for (FItem* item : m_Items) 
		{
			if (item->Id == ItemId)
			{
				result = Cast<T>(item);

				break;
			}
		}

		return result;
	}

	/**
	 * @fn	template<typename T> TArray<T*> UInventoryComponent::GetItems() const
	 *
	 * @brief	Gets all items with a specific type.
	 *
	 * @tparam	T	Generic type parameter.
	 *
	 * @returns	Null if it fails, else the items.
	 */
	template<typename T>
	TArray<T*> GetItems() const
	{
		TArray<T*> result;

		for (FItem* item : m_Items) 
		{
			if (T* castedItem = Cast<T>(item)) 
			{
				result.Add(castedItem);
			}
		}

		return result;
	}

protected:

	/**
	 * @fn	virtual void UInventoryComponent::BeginPlay() override;
	 *
	 * @brief	Will be called when the owning actor spawns or the component is added to a actor on runtime.
	 */
	virtual void BeginPlay() override;
		
private:

	/** Max inventory slots. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blood & Soul | Storage", meta = (AllowPrivateAccess = "true"))
	int MaxSlots;

	/** @brief	Inventory items. */
	TArray<FItem*> m_Items;

};
