// Fill out your copyright notice in the Description page of Project Settings.

#include "NoiseGenerator.h"

ANoiseGenerator::ANoiseGenerator()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANoiseGenerator::BeginPlay()
{
	Super::BeginPlay();

	GenerateNoise();
	GeneratePositions();

	//Spawns objects to display the generated noise
	PopulatePositions();
}

//Generates 2D Perlin noise
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

//Makes a 2D grid of positions to later be populated by objects based on the 2D perlin noise
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

//Spawns objects at generated positions based on 2D perlin noise.
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

void ANoiseGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

