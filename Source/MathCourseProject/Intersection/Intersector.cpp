// Fill out your copyright notice in the Description page of Project Settings.


#include "Intersector.h"

// Sets default values
AIntersector::AIntersector()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

bool AIntersector::SphereSphereIntersection(FVector Sphere1Pos, float Sphere1Radius, FVector Sphere2Pos,
	float Sphere2Radius)
{
	FVector Distance = Sphere1Pos - Sphere2Pos;
	float SummedRadius = Sphere1Radius + Sphere2Radius;

	return Distance.Dot(Distance) <= SummedRadius * SummedRadius;
}

// Called when the game starts or when spawned
void AIntersector::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AIntersector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if(SphereSphereIntersection(GetActorLocation(),(GetActorScale().X)*100, OtherActor->GetActorLocation(), (OtherActor->GetActorScale().X))*100)
	{
		OnIntersect();
	}
}

