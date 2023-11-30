// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NoiseGenerator.generated.h"

UCLASS()
class MATHCOURSEPROJECT_API ANoiseGenerator : public AActor
{
	GENERATED_BODY()

public:
	ANoiseGenerator();

	//Actor class used to display the generated noise
	UPROPERTY(EditAnywhere, Category="Noise")
	TSubclassOf<AActor> ObjectToSpawn;

	//**
	//Noise settings
	//**
	UPROPERTY(EditAnywhere, Category="Noise")
	int Resolution;
	UPROPERTY(EditAnywhere, Category="Noise")
	float Strength;
	UPROPERTY(EditAnywhere, Category="Noise")
	float Scale;
	UPROPERTY(EditAnywhere, Category="Noise")
	float DistanceBetweenPoints;
	UPROPERTY(EditAnywhere, Category="Noise")
	FVector2D Offset;

private:
	//Generated noise variables
	TArray<float> NoiseArray;
	TArray<FVector> PositionArray;

protected:
	virtual void BeginPlay() override;

	void GenerateNoise();
	void GeneratePositions();
	void PopulatePositions();

public:
	virtual void Tick(float DeltaTime) override;
};
