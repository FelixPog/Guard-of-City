// Fill out your copyright notice in the Description page of Project Settings.


#include "GrappleHookComponent.h"
#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TimelineComponent.h"

#include "DrawDebugHelpers.h"

UGrappleHookComponent::UGrappleHookComponent()
{
	CableComponent = CreateDefaultSubobject<UCableComponent>(FName(TEXT("CableComponent")));

	if (CableComponent != nullptr)
	{
		CableComponent->SetRelativeTransform(FTransform::Identity);
		CableComponent->bAttachStart = true;
		CableComponent->bAttachEnd = true;
		CableComponent->CableLength = 0.0f;
		CableComponent->SetVisibility(false);
	}
}

void UGrappleHookComponent::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));


	if (CableComponent != nullptr && PlayerCharacter != nullptr)
	{
		//CableComponent->AttachToComponent(PlayerCharacter->GetCapsuleComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	}

}

bool UGrappleHookComponent::UseCapacity()
{
	if (!IsCapacityReady)
	{
		return false;
	}
	
	return CheckForSurface();
}

bool UGrappleHookComponent::CheckForSurface()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	if (PlayerCharacter == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter nullptr"));
		return false;
	}

	const FVector PlayerLocation = PlayerCharacter->GetFirstPersonCameraComponent()->GetComponentLocation();
	const FVector EndTrace = (PlayerCharacter->GetFirstPersonCameraComponent()->GetForwardVector() * GrappleHookDistance) + PlayerLocation;

	FHitResult Hit;
	const FCollisionQueryParams QueryParams = FCollisionQueryParams(SCENE_QUERY_STAT(WeaponTrace), true, PlayerCharacter);

	if (CapacitySound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, CapacitySound, GetOwner()->GetActorLocation());
	}
	
	if (GetWorld()->LineTraceSingleByChannel(Hit, PlayerLocation, EndTrace, ECC_Visibility, QueryParams))
	{
		HitLocation = Hit.ImpactPoint;
		StartCooldown();
		PrepareLaunch();
		GetOwner()->GetWorldTimerManager().SetTimer(PrelaunchTimerHandle, this, &UGrappleHookComponent::LaunchPlayer, 1.0f, false, TimerDelay);
		return true;
	}

	return false;
}

void UGrappleHookComponent::PrepareLaunch()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->LaunchCharacter(FVector(0.0f, 0.0f, PrelaunchStrengh), true, true);
		}
}

void UGrappleHookComponent::LaunchPlayer()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	if (PlayerCharacter != nullptr)
	{
		FVector MovementDirection = HitLocation - PlayerCharacter->GetActorLocation();
		MovementDirection.Normalize();

		PlayerCharacter->LaunchCharacter(MovementDirection * TravelSpeed, false, false);
	}
}


