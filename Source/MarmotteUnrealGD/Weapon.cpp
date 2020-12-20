// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "DamageComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	DamageComponent = CreateDefaultSubobject<UDamageComponent>(TEXT("DamageComp"));
	
	MunitionsLeft = MaxMunitions;
	TimeBetweenShot = 1 / ShotPerSeconds;
}

void AWeapon::StartFire(APlayerCharacter * PlayerRef)
{
	UE_LOG(LogTemp, Error, TEXT("Function StartFire from mother class Weapon is used, it should not "));
}

void AWeapon::StopFire()
{
	UE_LOG(LogTemp, Error, TEXT("Function StopFire from mother class Weapon is used, it should not "));
}

void AWeapon::StartReload()
{
    if (IsReloading || MunitionsLeft == MaxMunitions) 
	{
		return;
    }

	if (ReloadSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ReloadSound, GetActorLocation());
	}
	
	IsReloading = true;
	GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &AWeapon::Reload, 1.f, false, ReloadingTime);
}

void AWeapon::Reload()
{
    // TODO Add some Reloading animation
	MunitionsLeft = MaxMunitions;
	IsReloading = false;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	MunitionsLeft = MaxMunitions;
	
}

void AWeapon::FireShot()
{
	if (PlayerCharacter == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerCharacter is nullptr in  Weapon::FireShot()"));
		return;
	}

	if (IsReloading)
	{
		return;
	}
	
    if (MunitionsLeft <= 0) 
	{
	    //TODO Add feed back for player to reload (visual or sound)
		StartReload();
		return;
    }
	FHitResult Hit;

	const FVector StartTrace = PlayerCharacter->GetFirstPersonCameraComponent()->GetComponentLocation();
	const FVector EndTrace = (PlayerCharacter->GetFirstPersonCameraComponent()->GetForwardVector() * WeaponRange) + StartTrace;

	FCollisionQueryParams QueryParams = FCollisionQueryParams(SCENE_QUERY_STAT(WeaponTrace), false, this);

	if (GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_Visibility, QueryParams))
	{		
		if (ImpactParticles != nullptr)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, FTransform(Hit.ImpactNormal.Rotation(), Hit.ImpactPoint));
		}

		if (Hit.GetActor()->ActorHasTag("Enemy"))
		{
			if (DamageComponent != nullptr)
			{
				UGameplayStatics::ApplyDamage(Hit.GetActor(), DamageComponent->GetDamage(), PlayerCharacter->GetController(), this, UDamageType::StaticClass());
			}
		}
	}

	if (MuzzleParticles != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleParticles, FP_Gun->GetSocketTransform(FName("Muzzle")));
	}

	// try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = PlayerCharacter->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}

	MunitionsLeft--;
}

void AWeapon::EnableCanShoot()
{
	CanShoot = true;
	GetWorldTimerManager().ClearTimer(RateWeaponTimerHandle);
}

