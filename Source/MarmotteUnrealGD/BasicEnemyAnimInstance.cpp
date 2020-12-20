// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicEnemyAnimInstance.h"
#include "Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBasicEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AEnemy* MyEnemy = Cast<AEnemy>(TryGetPawnOwner());
	if (MyEnemy != nullptr)
	{
		const float MoveSpeed = MyEnemy->GetCharacterMovement()->Velocity.Size();

		IsWalking = (!FMath::IsNearlyZero(MoveSpeed));

		if (IsWalking)
		{
			
			const float MaxSpeed = MyEnemy->GetCharacterMovement()->MaxWalkSpeed;
			WalkBlendRatio = (MoveSpeed / MaxSpeed) * 100.0f;
		}
	}
}
