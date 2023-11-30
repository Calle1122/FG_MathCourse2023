// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Intersector.generated.h"

UCLASS()
class MATHCOURSEPROJECT_API AIntersector : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AIntersector();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intersection")
	TObjectPtr<AActor> OtherActor;

	bool SphereSphereIntersection(FVector Sphere1Pos, float Sphere1Radius, FVector Sphere2Pos, float Sphere2Radius);

	UFUNCTION(BlueprintImplementableEvent, Category = "Intersection")
	void OnIntersect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
