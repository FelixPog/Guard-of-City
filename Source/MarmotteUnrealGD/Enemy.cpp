// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "BasicEnemyAnimInstance.h"
#include "HPComponent.h"
#include "PlayerCharacter.h"
#include "Animation/AnimInstance.h"
#include "DamageComponent.h"
#include "Fortress.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HPComponent = CreateDefaultSubobject<UHPComponent>(FName(TEXT("HealthComponent")));
	DamageComponent = CreateDefaultSubobject<UDamageComponent>(FName(TEXT("DamageComponent")));
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	TimerBetweenAttack = 1 / AttackSpeed;
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::Attack(AActor* TargetToAttack)
{
	if (TargetToAttack != nullptr)
	{
		UGameplayStatics::ApplyDamage(TargetToAttack, DamageComponent->GetDamage(), this->GetController(), this, UDamageType::StaticClass());
	}
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if (HPComponent == nullptr)
	{
		return 0.0f;
	}

	OnHPChange();
	
	if (HPComponent->TakeDamage(DamageAmount))
	{
		this->Destroy();
	}
	
	return DamageAmount;
}

void AEnemy::StartAttack()
{
	APlayerCharacter* PlayerCharacter = static_cast<APlayerCharacter*>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (PlayerCharacter == nullptr)
	{
		return;
	}

	TArray<AActor*> Fortress;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Fortress", Fortress);
		
	UBasicEnemyAnimInstance* EnemyAnim = Cast< UBasicEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (EnemyAnim != nullptr && Fortress[0] != nullptr)
	{		
		if (CanAttack && GetDistanceTo(PlayerCharacter) <= AttackRange)
		{
			Attack(PlayerCharacter);
		}		
		else if (CanAttack && GetDistanceTo(Fortress[0]) - 200 <= AttackRange)
		{
			Attack(Fortress[0]);
		}

		StartAttackCooldown();
		EnemyAnim->IsAttacking = true;
	}
}

void AEnemy::StopAttack()
{
	UBasicEnemyAnimInstance* EnemyAnim = Cast< UBasicEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (EnemyAnim != nullptr)
	{
		EnemyAnim->IsAttacking = false;
	}
}

void AEnemy::ActivateCanAttack()
{
	CanAttack = true;
	UBasicEnemyAnimInstance* EnemyAnim = Cast< UBasicEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (EnemyAnim != nullptr)
	{
		EnemyAnim->IsAttacking = false;
	}
}

void AEnemy::StartAttackCooldown()
{
	CanAttack = false;
	GetWorldTimerManager().SetTimer(AttackCoolDownTimerHandle, this, &AEnemy::EnableAttackCooldown, TimerBetweenAttack, false);
}

void AEnemy::EnableAttackCooldown()
{
	CanAttack = true;
	GetWorldTimerManager().ClearTimer(AttackCoolDownTimerHandle);
}

bool AEnemy::GetCanAttack()
{
	return CanAttack;
}





