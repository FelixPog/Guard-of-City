// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"
#include "HPComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapon.h"
#include "FireProjectileComponent.h"
#include "GrappleHookComponent.h"
#include "WindBumpCapacityComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

        // Create HPComponent
	HPComponent = CreateDefaultSubobject<UHPComponent>(FName(TEXT("HealthComponent")));
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

    if (PrimaryWeaponClass != nullptr) 
    {
		PrimaryWeapon = GetWorld()->SpawnActor<AWeapon>(PrimaryWeaponClass, FTransform::Identity);

	if (PrimaryWeapon != nullptr)
	{
	        PrimaryWeapon->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
    }

    if (FirstCapacityClass != nullptr) 
    {
        FirstCapacityComponent = NewObject<UCapacityComponent>(this, FirstCapacityClass);
	FirstCapacityComponent->RegisterComponent();

    }

    if (SecondCapacityClass != nullptr)
    {
            SecondCapacityComponent = NewObject<UCapacityComponent>(this, SecondCapacityClass);
	  SecondCapacityComponent->RegisterComponent();
    }

    if (ThirdCapacityClass != nullptr)
    {
            ThirdCapacityComponent = NewObject<UCapacityComponent>(this, ThirdCapacityClass);
            ThirdCapacityComponent->RegisterComponent();
    }

    if (FourthCapacityClass != nullptr)
    {
	FourthCapacityComponent = NewObject<UCapacityComponent>(this, FourthCapacityClass);
	FourthCapacityComponent->RegisterComponent();
    }

    if (FifthCapacityClass != nullptr)
    {
	  FifthCapacityComponent = NewObject<UCapacityComponent>(this, FifthCapacityClass);
	  FifthCapacityComponent->RegisterComponent();
    }
	
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerCharacter::StopFire);

        // Bind reload event
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &APlayerCharacter::Reload);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

        // Bind capacities event
	PlayerInputComponent->BindAction("FirstCapacity", IE_Pressed, this, &APlayerCharacter::UseFirstCapacity);
	PlayerInputComponent->BindAction("SecondCapacity", IE_Pressed, this, &APlayerCharacter::UseSecondCapacity);
	PlayerInputComponent->BindAction("ThirdCapacity", IE_Pressed, this, &APlayerCharacter::UseThirdCapacity);
	PlayerInputComponent->BindAction("MovementSpeedBuff", IE_Pressed, this, &APlayerCharacter::UseFourthCapacity);
	PlayerInputComponent->BindAction("SecondaryFire", IE_Pressed, this, &APlayerCharacter::UseFifthCapacity);

        // Bind shop access event
	/*PlayerInputComponent->BindAction("ShopAccess", IE_Pressed, this, &APlayerCharacter::AccessShop);*/
}

void APlayerCharacter::StartFire()
{
    if (PrimaryWeapon == nullptr)
	{
	    return;
    }
	PrimaryWeapon->StartFire(this);
}

void APlayerCharacter::StopFire()
{
	if (PrimaryWeapon == nullptr)
	{
		return;
	}
	PrimaryWeapon->StopFire();
}

void APlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void APlayerCharacter::Reload()
{
        if (PrimaryWeapon !=nullptr) 
	{
	      PrimaryWeapon->StartReload();
        }
}

void APlayerCharacter::UseFirstCapacity()
{
    if (FirstCapacityComponent == nullptr)
	{
		return;
    }

    if(FirstCapacityComponent->UseCapacity())
    {
		OnFirstCapacityUse();
    }
}

void APlayerCharacter::UseSecondCapacity()
{
	if (SecondCapacityComponent == nullptr)
	{
		return;
	}
	
	if(SecondCapacityComponent->UseCapacity())
	{
		OnSecondCapacityUse();
	}
}

void APlayerCharacter::UseThirdCapacity()
{
	if (ThirdCapacityComponent == nullptr)
	{
		return;
	}
	
	if(ThirdCapacityComponent->UseCapacity())
	{
		OnThirdCapacityUse();
	}
}

void APlayerCharacter::UseFourthCapacity()
{
	if (FourthCapacityComponent == nullptr)
	{
		return;
	}
	
	if (FourthCapacityComponent->UseCapacity())
	{
		OnFourthCapacityUse();
	}
}

void APlayerCharacter::UseFifthCapacity()
{
	if (FifthCapacityComponent == nullptr)
	{
		return;
	}
	
	if (FifthCapacityComponent->UseCapacity())
	{
		OnFifthCapacityUse();
	}
}


float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,AActor* DamageCauser)
{
	if (HPComponent == nullptr)
	{
		return 0.0f;
	}

	if (HPComponent->TakeDamage(DamageAmount))
	{
		OnDeath();
		return DamageAmount;
	};

	return DamageAmount;
}

