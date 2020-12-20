// Fill out your copyright notice in the Description page of Project Settings.


#include "Fortress.h"

#include "DamageComponent.h"
#include "HPComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include  "PlayerCharacter.h"


// Sets default values
AFortress::AFortress()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FortressMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("FortressMesh")));
	if (FortressMesh != nullptr)
	{
		SetRootComponent(FortressMesh);
	}

	HPComponent = CreateDefaultSubobject<UHPComponent>(FName(TEXT("HPComponent")));
		
}

// Called when the game starts or when spawned
void AFortress::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFortress::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AFortress::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	if (HPComponent == nullptr) 
	{
		return 0.0f;
	}
	
	HPComponent->TakeDamage(DamageAmount);

	if (HPComponent->GetHeathPercentage() <= 0.0f)
	{
		APlayerCharacter* PlayerCharacter = static_cast<APlayerCharacter*>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		if (PlayerCharacter != nullptr)
		{
			PlayerCharacter->OnDeath();
		}
	}
	
	return DamageAmount;
}


