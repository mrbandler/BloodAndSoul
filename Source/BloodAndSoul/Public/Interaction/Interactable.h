// Copyright (c) fivefingergames 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractorMovedIntoRange);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractorMovedOutOfRange);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteraction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDisengage);

UCLASS()
class BLOODANDSOUL_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	

	/** Will be fired when a interactor is in range. */
	UPROPERTY(BlueprintAssignable, Category = "Blood & Soul | Events")
	FOnInteractorMovedIntoRange OnInteractorMovedIntoRange;

	/** Will be fired when a interactor moves out of range. */
	UPROPERTY(BlueprintAssignable, Category = "Blood & Soul | Events")
	FOnInteractorMovedOutOfRange OnInteractorMovedOutOfRange;

	/** Will be fired when the player wants to interact. */
	UPROPERTY(BlueprintAssignable, Category = "Blood & Soul | Events")
	FOnInteraction OnInteraction;

	/** Will be fired when the player wants to interact. */
	UPROPERTY(BlueprintAssignable, Category = "Blood & Soul | Events")
	FOnDisengage OnDisengage;

	/**
	 * @fn	AInteractable::AInteractable();
	 *
	 * @brief	Default constructor.
	 */
	AInteractable();

	/**
	 * @fn	virtual void AInteractable::Tick(float DeltaTime) override;
	 *
	 * @brief	Will be called every frame.
	 *
	 * @param	DeltaTime	The delta time.
	 */
	virtual void Tick(float DeltaTime) override;

	/**
	 * @fn	virtual void AInteractable::Interact();
	 *
	 * @brief	Kicks the interaction process off.
	 */
	UFUNCTION(BlueprintCallable, Category = "Blood & Soul | Interaction")
	virtual void Interact();

	/**
	 * @fn	virtual void AInteractable::Disengage();
	 *
	 * @brief	Kicks the disengament process off.
	 */
	UFUNCTION(BlueprintCallable, Category = "Blood & Soul | Interaction")
	virtual void Disengage();

protected:

	/**
	 * @fn	virtual void AInteractable::BeginPlay() override;
	 *
	 * @brief	Will be called when this actor spawns.
	 */
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, Category = "Blood & Soul | Interaction")
	class APlayerCharacter* GetInteractor() const;

private:

	/** Mesh for the interactable. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	/** Trigger sphere. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* TriggerSphere;

	/** @brief	The interactor. */
	class APlayerCharacter* m_Interactor;

	/**
	 * @fn	void AInteractable::OnComponentBeginOverlap();
	 *
	 * @brief	Executes the component begin overlap action.
	 */
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	/**
	 * @fn	void AInteractable::OnComponentEndOverlap();
	 *
	 * @brief	Executes the component end overlap action.
	 */
	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
