// Copyright (c) fivefingergames 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShopComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLOODANDSOUL_API UShopComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	/**
	 * @fn	UShopComponent::UShopComponent();
	 *
	 * @brief	Default constructor.
	 */
	UShopComponent();

	/**
	 * @fn	virtual void UShopComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	 *
	 * @brief	Will be called every frame.
	 *
	 * @param 		  	DeltaTime			The delta time.
	 * @param 		  	TickType			Type of the tick.
	 * @param [in,out]	ThisTickFunction	If non-null, this tick function.
	 */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	/**
	 * @fn	virtual void UShopComponent::BeginPlay() override;
	 *
	 * @brief	Will be called when the owning actor spawns or the component is added to an actor durin runtime.
	 */
	virtual void BeginPlay() override;

};
