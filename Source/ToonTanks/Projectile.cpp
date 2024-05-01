// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = 100.0f;
	ProjectileMovement->MaxSpeed = 400.0f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Get the owner of this projectile. The owner is typically the pawn that fired the projectile.
	AActor* MyOwner = GetOwner();

	// If the projectile doesn't have an owner, return immediately. This is a safety check to ensure that the projectile has an owner.
	if(MyOwner==nullptr) return;

	// Get the controller that instigated the action. This is typically the player controller or AI controller that controls the pawn that fired the projectile.
	AController* MyOwnerInstigator = GetOwner()->GetInstigatorController();

	// Get a reference to the UDamageType class. This is used to specify the type of damage that the projectile deals.
	UClass* DamageTypeClass = UDamageType::StaticClass();

	// Check if the actor that the projectile hit (OtherActor) is valid and is not the projectile itself or the owner of the projectile.
	// If these conditions are met, the code inside the if statement is executed. This is where you would typically apply damage to the hit actor or trigger some other effect.
	if(OtherActor && OtherActor != this && OtherActor !=MyOwner)
	{
		// Code to be executed when the projectile hits another actor goes here.
		// Apply damage to the actor that was hit by the projectile.
		// The UGameplayStatics::ApplyDamage function is used to apply damage to an actor in the game.
		// The parameters are as follows:
		// - OtherActor: The actor that was hit by the projectile.
		// - Damage: The amount of damage to apply. This is a float value.
		// - MyOwnerInstigator: The controller that instigated the action. This is typically the player controller or AI controller that controls the pawn that fired the projectile.
		// - this: The actor that is causing the damage. In this case, it's the projectile itself.
		// - DamageTypeClass: A reference to the UDamageType class. This is used to specify the type of damage that the projectile deals.
		UGameplayStatics::ApplyDamage(OtherActor,Damage,MyOwnerInstigator,this,DamageTypeClass);
		Destroy();
	}
}
