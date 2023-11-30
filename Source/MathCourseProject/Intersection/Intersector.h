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
	AIntersector();

	//Other actor used for checking intersections with this actor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intersection")
	TObjectPtr<AActor> OtherActor;

	//Checks intersections between two spheres
	bool SphereSphereIntersection(FVector Sphere1Pos, float Sphere1Radius, FVector Sphere2Pos, float Sphere2Radius);

	//BP called event whenever there is an intersection between this Actor and "OtherActor"
	UFUNCTION(BlueprintImplementableEvent, Category = "Intersection")
	void OnIntersect();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
