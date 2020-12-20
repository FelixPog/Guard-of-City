// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"



class UDamageComponent;
class UHPComponent;
UCLASS()
class MARMOTTEUNREALGD_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Enemy)
	UHPComponent* HPComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Enemy)
	UDamageComponent* DamageComponent = nullptr;

	UPROPERTY(EditAnywhere, Category = Enemy)
	float AttackRange = 150.0f;

	// Number of attack the enemy can do during one second
	UPROPERTY(EditAnywhere, Category = Enemy)
	float AttackSpeed = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AnimMontage = nullptr;

	UFUNCTION(BlueprintImplementableEvent, Category = Enemy)
	void OnHPChange();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Attack(AActor* TargetToAttack);
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void StartAttack();

	void StopAttack();

	void ActivateCanAttack();

	void StartAttackCooldown();
	void EnableAttackCooldown();

	bool GetCanAttack();
	
private:
	FTimerHandle AttackCoolDownTimerHandle;
	float TimerBetweenAttack = 0.0f;
	bool CanAttack = true;

};
