// Fill out your copyright notice in the Description page of Project Settings.
#include "StateDemonstrator.h"
#include "DrawDebugHelpers.h"
#include "MathCourseProject/Constants.h"
#include "MathCourseProject/Context/ContextHelpers.h"

AStateDemonstrator::AStateDemonstrator()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
}

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

	//Interpolation

	if(T < 1)
	{
		T += DeltaTime * InterpSpeed;

		FVector NewPos = FMath::Lerp(CurrentPos, TargetPos, T);
		NewPos += FVector(0, 0, ZCurve->GetFloatValue(T));
		
		SetActorLocation(NewPos);

		FRotator NewRot = FMath::Lerp(CurrentRot, TargetRot, T);
		NewRot += FRotator(RotCurve->GetVectorValue(T).X, RotCurve->GetVectorValue(T).Y, RotCurve->GetVectorValue(T).Z);
		
		SetActorRotation(NewRot);
	}
}

//Enables viewport tick
bool AStateDemonstrator::ShouldTickIfViewportsOnly() const
{
	return false;
}

//Moves character
void AStateDemonstrator::MoveToRandomPosition()
{
	CurrentPos = GetActorLocation();
	CurrentRot = GetActorRotation();
	
	float newX = FMath::RandRange(-1000.f, 1000.f);
	float newY = FMath::RandRange(-750.f, 750.f);
	
	TargetPos = (FVector(newX, newY, 0));
	TargetRot = (FRotator(0, FMath::RandRange(0.f, 360.f), 0));

	T = 0;
}

void AStateDemonstrator::UpdateUnitContext()
{
	//Updates the current context
	GetContext();
}

void AStateDemonstrator::SimulateFightFromCurrentContext()
{
	//Does [something] based on current context (ex. deals damage, takes damage)
	ContextResponder();
}

void AStateDemonstrator::DoToggleFightStance()
{
	ToggleFightStance();
}

void AStateDemonstrator::GetContext()
{
	for (auto Other : Demonstrators)
	{
		if(!IsValid(Other)) return;
		
		Context = NewObject<UContextHelpers>()->GetRelativeContext(this, Other);
	}
}

void AStateDemonstrator::ContextResponder()
{
	//Checks for other unit in range and deals damage to them
	if(TEST_BIT(Context, ERelativeContext::Seen) && TEST_BIT(Context, ERelativeContext::Close))
	{
		if(AStateDemonstrator* OtherUnit = StaticCast<AStateDemonstrator*>(Demonstrators[0]))
		{
			OtherUnit->Health -= 25.f;
		}
	}
}
