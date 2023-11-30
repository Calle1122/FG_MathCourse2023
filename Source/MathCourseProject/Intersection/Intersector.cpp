// Fill out your copyright notice in the Description page of Project Settings.

#include "Intersector.h"

AIntersector::AIntersector()
{
	PrimaryActorTick.bCanEverTick = true;
}

//Intersection implementation (check if two spheres are intersecting)
bool AIntersector::SphereSphereIntersection(FVector Sphere1Pos, float Sphere1Radius, FVector Sphere2Pos,
	float Sphere2Radius)
{
	FVector Distance = Sphere1Pos - Sphere2Pos;
	float SummedRadius = Sphere1Radius + Sphere2Radius;

	return Distance.Dot(Distance) <= SummedRadius * SummedRadius;
}

void AIntersector::BeginPlay()
{
	Super::BeginPlay();
}

void AIntersector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Calls BP event whenever this actor and "OtherActor" intersects
	if(SphereSphereIntersection(GetActorLocation(),(GetActorScale().X)*100, OtherActor->GetActorLocation(), (OtherActor->GetActorScale().X))*100)
	{
		OnIntersect();
	}
}

