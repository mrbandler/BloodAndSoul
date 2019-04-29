// Copyright (c) fivefingergames 2019

#include "ShopComponent.h"

UShopComponent::UShopComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UShopComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UShopComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

