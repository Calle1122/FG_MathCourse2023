// Fill out your copyright notice in the Description page of Project Settings.
#include "StateDemonstrator.h"
#include "DrawDebugHelpers.h"
#include "MathCourseProject/Constants.h"
#include "MathCourseProject/Context/ContextHelpers.h"

//Constructor
AStateDemonstrator::AStateDemonstrator()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
}

//Tick (every frame)
//TODO: clean up and make functions
void AStateDemonstrator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector Cross = FVector::CrossProduct(GetActorForwardVector(), GetActorRightVector());

	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100.f, FColor::Red);
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorRightVector() * 100.f, FColor::Green);
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + Cross * 100.f, FColor::Blue);
	
	if(!DrawArc)
		return;
	
	DrawDebugCone(
		GetWorld(),
		GetActorLocation(),
		GetActorForwardVector(),
		CONST_Range,
		FMath::DegreesToRadians(CONST_Angle * .5f),
		0.f,
		1,
		FColor::Green
		);
}

//Enables viewport tick
bool AStateDemonstrator::ShouldTickIfViewportsOnly() const
{
	return true;
}

//Moves character
void AStateDemonstrator::MoveToRandomPosition()
{
	//Get random location on map and move character to it
	float newX = FMath::RandRange(-1000.f, 1000.f);
	float newY = FMath::RandRange(-750.f, 750.f);
	
	StaticMeshComponent->SetWorldLocation(FVector(newX, newY, 100.f));

	//Get random z rotation and set it
	StaticMeshComponent->SetRelativeRotation(FRotator(0, FMath::RandRange(0.f, 360.f), 0));
}

//Updates current context
void AStateDemonstrator::UpdateUnitContext()
{
	//Updates the current context
	GetContext();
}

//Starts fight
void AStateDemonstrator::SimulateFightFromCurrentContext()
{
	//Does [something] based on current context (ex. deals damage, takes damage)
	ContextResponder();
}

//Getting of context
void AStateDemonstrator::GetContext()
{
	for (auto Other : Demonstrators)
	{
		if(!IsValid(Other)) return;
		
		Context = NewObject<UContextHelpers>()->GetRelativeContext(this, Other);
	}
}

//Responding of context
void AStateDemonstrator::ContextResponder()
{
	//If other unit is seen and close, deal 25 damage to them
	if(TEST_BIT(Context, ERelativeContext::Seen) && TEST_BIT(Context, ERelativeContext::Close))
	{
		if(AStateDemonstrator* OtherUnit = StaticCast<AStateDemonstrator*>(Demonstrators[0]))
		{
			OtherUnit->Health -= 25.f;
		}
	}
}
