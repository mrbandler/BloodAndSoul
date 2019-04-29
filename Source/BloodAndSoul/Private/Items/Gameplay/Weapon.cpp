// Copyright (c) fivefingergames 2019

#include "Items/Gameplay/Weapon.h"
#include "Items/Database/WeaponItem.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

const FName AWeapon::DrawDebugTraceTag = TEXT("DDTWeapon");


AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	AttackTraceStart = CreateDefaultSubobject<UArrowComponent>(TEXT("AttackTraceStart"));
	AttackTraceStart->ArrowSize = 0.2f;
	AttackTraceStart->SetupAttachment(RootComponent);

	AttackTraceEnd = CreateDefaultSubobject<UArrowComponent>(TEXT("AttackTraceEnd"));
	AttackTraceEnd->ArrowSize = 0.2f;
	AttackTraceEnd->SetupAttachment(RootComponent);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	EnableDebugDrawings();
}

void AWeapon::EnableDebugDrawings()
{
	if (bDebug == true)
	{
		GetWorld()->DebugDrawTraceTag = AWeapon::DrawDebugTraceTag;
	}
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::SetWeaponItem(FWeaponItem* WeaponItem)
{
	m_WeaponItem = WeaponItem;
}

int32 AWeapon::GetStaminaCost() const
{
	return m_WeaponItem->AttackStaminaCost;
}

void AWeapon::AttackBegin()
{
	hitEnemies.Empty();
}

/**
 * @fn	void AWeapon::AttackTick()
 *
 * @brief	Attack tick
 */

void AWeapon::AttackTick()
{
	ACharacter* owningCharacter = GetOwningCharacter();
	if (owningCharacter != nullptr)
	{
		FVector traceStart = AttackTraceStart->GetComponentLocation();
		FVector traceEnd = AttackTraceEnd->GetComponentLocation();
		UWorld* world = GetWorld();

		FCollisionQueryParams collisionQueryParams;
		collisionQueryParams.AddIgnoredActor(owningCharacter);
		if (bDebug == true)
		{
			collisionQueryParams.TraceTag = AWeapon::DrawDebugTraceTag;
		}

		FHitResult hitResult(ForceInit);
		bool traceResult = world->LineTraceSingleByChannel(hitResult, traceStart, traceEnd, ECollisionChannel::ECC_MAX, collisionQueryParams);
		if (traceResult == true)
		{
			if (hitResult.Actor->IsA<APawn>() == true)
			{
				APawn* hitEnemy = Cast<APawn>(hitResult.Actor);
				if (hitEnemies.Contains(hitEnemy) == false)
				{
					hitEnemies.Add(hitEnemy);
					UGameplayStatics::ApplyDamage(hitResult.Actor.Get(), m_WeaponItem->Damage, owningCharacter->GetController(), owningCharacter, m_WeaponItem->DamageType);
				}
			}
		}
	}
}

void AWeapon::AttackEnd()
{
	// Nothing to to here as of right now.
}

ACharacter* AWeapon::GetOwningCharacter()
{
	ACharacter* result = nullptr;

	AActor* ownerActor = this->GetOwner();
	if (ownerActor != nullptr && ownerActor->IsA<ACharacter>() == true)
	{
		result = Cast<ACharacter>(ownerActor);
	}

	return result;
}
