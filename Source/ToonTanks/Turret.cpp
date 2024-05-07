// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Tank.h"

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->AController::GetPawn());

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATurret::CheckFireCondition, FireRate, true);
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(InFireRange())
	{
			RotateTurret(Tank->GetActorLocation());
	}
}

void ATurret::CheckFireCondition()
{
	if(InFireRange())
	{
		Fire();
	}
}

bool ATurret::InFireRange()
{
	if(Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		return Distance <= FireRange;
	}
	return false;
}

void ATurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}