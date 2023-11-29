// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseGenerator.h"


// Sets default values
ANoiseGenerator::ANoiseGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANoiseGenerator::BeginPlay()
{
	Super::BeginPlay();

	GenerateNoise();
	GeneratePositions();

	PopulatePositions();
}

void ANoiseGenerator::GenerateNoise()
{
	NoiseArray.SetNum((Resolution + 1) * (Resolution + 1));

	for (auto Y = 0; Y <= Resolution; Y++)
	{
		for (auto X = 0; X <= Resolution; X++)
		{
			const FVector2D Position = FVector2D(
				((static_cast<float>(X) + Offset.X) + .1f) * Scale,
				((static_cast<float>(Y) + Offset.Y) + .1f) * Scale);
			
			const int32 Index = Y * Resolution + X;
			NoiseArray[Index] = FMath::PerlinNoise2D(Position) * Strength;
		}
	}
}

void ANoiseGenerator::GeneratePositions()
{
	PositionArray.SetNum((Resolution + 1) * (Resolution + 1));

	for (auto Y = 0; Y <= Resolution; Y++)
	{
		for (auto X = 0; X <= Resolution; X++)
		{
			const FVector Position = FVector((-Resolution/2) + X, 0, (-Resolution/2) + Y) * DistanceBetweenPoints;
			
			const int32 Index = Y * Resolution + X;
			PositionArray[Index] = Position;
		}
	}
}

void ANoiseGenerator::PopulatePositions()
{
	for (auto Index = 0; Index <= ((Resolution) * (Resolution)); Index++)
	{
		if(NoiseArray[Index] > 0.0f)
		{
			GetWorld()->SpawnActor<AActor>(ObjectToSpawn, PositionArray[Index], FRotator(0, 0, 0));
		}
	}
}

// Called every frame
void ANoiseGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

