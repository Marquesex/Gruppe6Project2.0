// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_SAGN.h"
#include "PlayerProjectile.h"


// Sets default values
APlayerProjectile::APlayerProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox = this->FindComponentByClass<UCapsuleComponent>();

	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APlayerProjectile::OnOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerProjectile no collision box"));

	}
}

// Called every frame
void APlayerProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	SetProjectileLocation(DeltaTime);

	TimeToDestroy += DeltaTime;

	if (TimeToDestroy > 10.0f)
	{
		Destroy();
	}

	if (bCurvingBullet)
	{
		CurvingBulletTimer += DeltaTime;

		FRotator Temp = FRotator(0.0f, 5.0f, 0.0f) + GetActorRotation();

		SetActorRotation(Temp);

		if (CurvingBulletTimer > 10.0f)
		{
			bCurvingBullet = false;
			CurvingBulletTimer = 0.0f;
		}
	}
}

void APlayerProjectile::SetProjectileLocation(float DeltaTime)
{
	FVector NewLocation = GetActorLocation() + GetActorForwardVector() * DeltaTime * Speed;

	NewLocation.Z = 100.0f;

	SetActorLocation(NewLocation);
}

void APlayerProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Hit A Wall"));
	if (OtherActor->IsRootComponentStatic())
	{
		Destroy();
	}
}

void APlayerProjectile::SetCurvingBullet()
{
	bCurvingBullet = true;
	UE_LOG(LogTemp, Warning, TEXT("Curving Bullet SET!"));
	if (bCurvingBullet)
	{
		UE_LOG(LogTemp, Warning, TEXT("Curving Bullet is true!"))
	}
}