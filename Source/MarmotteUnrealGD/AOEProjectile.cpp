// Fill out your copyright notice in the Description page of Project Settings.


#include "AOEProjectile.h"
#include "DamageComponent.h"
#include "Kismet/GameplayStatics.h"

void AAOEProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// TODO Explode after time

	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (OtherActor->ActorHasTag("Enemy"))
		{
			DoAoeDamage();
			DestroyProjectile();
		}
	}
}

void AAOEProjectile::DoAoeDamage()
{
	TArray<AActor*> IgnoredActors;
	TArray<AActor*> GetActorBuffer;

	// Ignore Fortress
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Fortress"), GetActorBuffer);

	for (AActor* actor : GetActorBuffer)
	{
		IgnoredActors.Add(actor);
	}

	// Ignore player
	IgnoredActors.Add(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageComponent->GetDamage(), GetActorLocation(), DamageRadius, UDamageType::StaticClass(), IgnoredActors, this, UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetController(), true, ECollisionChannel::ECC_Visibility);

}
