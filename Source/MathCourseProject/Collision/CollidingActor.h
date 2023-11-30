// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollidingActor.generated.h"

UCLASS()
class MATHCOURSEPROJECT_API ACollidingActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACollidingActor();

	UPROPERTY(EditAnywhere, Category = "Collision")
	float TimeBetweenCollisionChecks = .2f;

	UPROPERTY(EditAnywhere, Category = "Collision")
	float MoveSpeed = 1.f;

	UPROPERTY(EditAnywhere, Category = "Collision")
	FVector MovementDirection;

	UPROPERTY(EditAnywhere, Category = "Collision")
	TArray<AActor*> OtherColliders;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool SpherePlaneIntersection(FVector SpherePosition, float SphereRadius, FVector PlanePosition, FVector PlaneNormal);

	float CollisionTimer;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
