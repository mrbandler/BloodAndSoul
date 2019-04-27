// Copyright (c) fivefingergames 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

//Forward declarations.
class UWeaponAttributesComponent;
class UArrowComponent;
class ACharacter;

UCLASS()
class BLOODANDSOUL_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	/**
	 * @fn	AWeapon::AWeapon();
	 *
	 * @brief	Default constructor
	 */
	AWeapon();

	/**
	 * @fn	virtual void AWeapon::Tick(float DeltaTime) override;
	 *
	 * @brief	Will be called every frame.
	 *
	 * @param	DeltaTime	Delta time.
	 */
	virtual void Tick(float DeltaTime) override;

	/**
	 * @fn	void AWeapon::SetWeaponItem(FWeaponItem WeaponItem);
	 *
	 * @brief	Sets the weapon item.
	 *
	 * @param	WeaponItem	Weapon item to set.
	 */
	void SetWeaponItem(struct FWeaponItem* WeaponItem);

	/**
	 * @fn	int32 AWeapon::GetStaminaCost() const;
	 *
	 * @brief	Returns the attack stamina cost.
	 *
	 * @returns	Stamina cost.
	 */
	int32 GetStaminaCost() const;

	/**
	 * @fn  void AWeapon::AttackStart();
	 *
	 * @brief   This method will be called on the start of the attack notify state.
	 * */
	void AttackBegin();

	/**
	 * @fn	void AWeapon::AttackTick();
	 *
	 * @brief	This method will be called on every tick of the attack notify state.
	 *
	 */
	void AttackTick();

	/**
	 * @fn  void AWeapon::AttackEnd();
	 *
	 * @brief   This method will be called on the end of the attack notify state.
	 */
	void AttackEnd();

	/**
	 * @fn	FORCEINLINE UStaticMeshComponent* AWeapon::GetMesh() const
	 *
	 * @brief	Returns the weapons mesh.
	 *
	 * @returns	Null if it fails, else the mesh.
	 */
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return Mesh; }

protected:

	/**
	 * @fn	virtual void AWeapon::BeginPlay() override;
	 *
	 * @brief	Will be called when this actor is spawned.
	 */
	virtual void BeginPlay() override;

private:

	/** The weapons mesh. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blood & Soul | Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	/** The attack trace start location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blood & Soul | Components", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* AttackTraceStart;

	/** The attack trace end location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blood & Soul | Components", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* AttackTraceEnd;

	/** Flag to enable debug feedback. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Soul & Vessel | Debugging", meta = (AllowPrivateAccess = "true"))
	bool bDebug = false;

	/** @brief   The draw debug trace tag. */
	static const FName DrawDebugTraceTag;

	/** @brief   The hit characters. This array will be filled with all hit characters on a single attack sweep. */
	TArray<APawn*> hitEnemies;

	/** @brief	The weapon item */
	FWeaponItem* m_WeaponItem;

	/**
	 * @fn  void AWeapon::EnableDebugDrawings();
	 *
	 * @brief   Enables the debug feedback.
	 */
	void EnableDebugDrawings();

	/**
	 * @fn  ACharacter* AWeapon::GetOwningCharacter();
	 *
	 * @brief   Returns the owning character.
	 *
	 * @return  Null if it fails, else the owning character.
	 */
	ACharacter* GetOwningCharacter();

};
