// Copyright (c) fivefingergames 2019

#include "Characters/Player/PlayerCharacter.h"
#include "Characters/Components/AttributesComponent.h"
#include "Items/Components/InventoryComponent.h"
#include "Items/Database/WeaponItem.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Public/EngineGlobals.h"

APlayerCharacter::APlayerCharacter()
{
	SetupDefaults();
	SetupSceneComponents();
	SetupActorComponents();
}

void APlayerCharacter::SetupDefaults()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	WalkSpeed = 600.f;
	SprintSpeed = 1000.f;
	SprintStaminaReduction = 1;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void APlayerCharacter::SetupSceneComponents()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	Weapon = CreateEditorOnlyDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(Cast<USceneComponent>(GetMesh()), TEXT("WeaponSocket"));
}

void APlayerCharacter::SetupActorComponents()
{
	Attributes = CreateDefaultSubobject<UAttributesComponent>(TEXT("Attributes"));
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FString maxStaminaMessage = "MaxStamina: " + FString::SanitizeFloat(Attributes->GetMaxStamina());
	FString staminaMessage = "Stamina: " + FString::SanitizeFloat(Attributes->GetStamina());
	FString maxHealthMessage = "MaxHealth: " + FString::SanitizeFloat(Attributes->GetMaxHealth());
	FString healthMessage = "Health: " + FString::SanitizeFloat(Attributes->GetHealth());

	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Black, maxStaminaMessage);
	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Black, staminaMessage);
	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Black, maxHealthMessage);
	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Black, healthMessage);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Repeat, this, &APlayerCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::StopSprinting);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAtRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpAtRate", this, &APlayerCharacter::LookUpAtRate);
}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::Sprint()
{
	if (Attributes->GetStamina() > 0 && Attributes->IsStaminaRegenerating() == false) 
	{
		if (GetCharacterMovement()->MaxWalkSpeed != SprintSpeed) {
			GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		}

		Attributes->ReduceStamina(SprintStaminaReduction);
		if (Attributes->GetStamina() <= 0)
		{
			StopSprinting();
		}
	}
}

void APlayerCharacter::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	Attributes->RegenerateStamina();
}

void APlayerCharacter::EquipWeapon(FWeaponItem* WeaponItem)
{
	Weapon->SetChildActorClass(WeaponItem->WeaponToEquip);
	AWeapon* weapon = Cast<AWeapon>(Weapon->GetChildActor());
	weapon->SetOwner(this);
	weapon->SetWeaponItem(WeaponItem);
}

AWeapon* APlayerCharacter::GetEquippedWeapon() const
{
	return Cast<AWeapon>(Weapon->GetChildActor());
}

void APlayerCharacter::Attack()
{
	AWeapon* weapon = GetEquippedWeapon();
	if (weapon != nullptr && Attributes->GetStamina() > 0) 
	{
		//TODO: We need a animation state component to let the animation play and execute the attack.

		Attributes->ReduceStamina(weapon->GetStaminaCost());
		Attributes->RegenerateStamina();
	}
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float result = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Attributes->ReduceHealth(DamageAmount);

	return result;
}
