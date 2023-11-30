// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingActor.h"


// Sets default values
ACollidingActor::ACollidingActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACollidingActor::BeginPlay()
{
	Super::BeginPlay();

	CollisionTimer = 0;

	MovementDirection = FVector(FMath::RandRange(1, 5), FMath::RandRange(1, 5), 0);
}

bool ACollidingActor::SpherePlaneIntersection(FVector SpherePosition, float SphereRadius, FVector PlanePosition,
	FVector PlaneNormal)
{
	const auto Distance = SpherePosition.Dot(PlaneNormal) - PlaneNormal.Dot(PlanePosition);
	const auto Intersection = FMath::Abs(Distance) <= SphereRadius;
		
	return Intersection;
}

// Called every frame
void ACollidingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (auto OtherActor: OtherColliders)
	{
		CollisionTimer = FMath::Max(0, CollisionTimer - DeltaTime);
		
		if(SpherePlaneIntersection(GetActorLocation(), GetActorScale().X*2, OtherActor->GetActorLocation(), OtherActor->GetActorUpVector()) && CollisionTimer == 0)
		{
			MovementDirection = FMath::GetReflectionVector(MovementDirection, OtherActor->GetActorUpVector());
			CollisionTimer = TimeBetweenCollisionChecks;
		}
	}

	FVector newLocation = GetActorLocation() + MovementDirection * MoveSpeed;
	SetActorLocation(newLocation);
}

