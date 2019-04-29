// Copyright (c) fivefingergames 2019

#include "Interaction/Interactable.h"
#include "Characters/Player/PlayerCharacter.h"
#include "Components/SphereComponent.h"

AInteractable::AInteractable()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Cast<USceneComponent>(Mesh);
	
	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));
	TriggerSphere->SetupAttachment(RootComponent);
	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AInteractable::OnComponentBeginOverlap);
	TriggerSphere->OnComponentEndOverlap.AddDynamic(this, &AInteractable::OnComponentEndOverlap);
}

void AInteractable::BeginPlay()
{
	Super::BeginPlay();
}

APlayerCharacter* AInteractable::GetInteractor() const
{
	return m_Interactor;
}

void AInteractable::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerCharacter* character = Cast<APlayerCharacter>(OtherActor)) 
	{
		m_Interactor = character;
		m_Interactor->SetInteractable(this);
		OnInteractorMovedIntoRange.Broadcast();
	}
}

void AInteractable::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (APlayerCharacter * character = Cast<APlayerCharacter>(OtherActor))
	{
		m_Interactor = character;
		m_Interactor->SetInteractable(nullptr);
		OnInteractorMovedOutOfRange.Broadcast();
	}
}

void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractable::Interact()
{
	OnInteraction.Broadcast();
}

void AInteractable::Disengage()
{
	OnDisengage.Broadcast();
}

