// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StateDemonstrator.generated.h"

UCLASS(hidecategories=(Input, Movement, Collision, Rendering, HLOD, WorldPartition, DataLayers, Replication, Physics, Networking, Actor, LevelInstance, Cooking))
class MATHCOURSEPROJECT_API AStateDemonstrator : public AActor
{
	GENERATED_BODY()

public:
	
	AStateDemonstrator();

	//** COMPONENTS **/
	
	//Mesh component
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Base")
	UStaticMeshComponent* StaticMeshComponent;

	//** EXTERNAL VARIABLES **/

	//Health
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="State", meta=(UIMin=0,UIMax=100))
	float Health;
	//Current Context
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="State", meta=(Bitmask, BitmaskEnum = "/Script/MathCourseProject.ERelativeContext"))
	int32 Context;
	//Related Demonstrators (Other actors that affect context)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Context")
	TArray<AActor*> Demonstrators;
	//Should Draw Arc (y/n)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Context")
	bool DrawArc;

protected:

	//** INTERNAL GAME FUNCTIONS **/

	//Get Current Context
	void GetContext();
	//Context Response (what happens next based on current context)
	void ContextResponder();
	
public:
	
	virtual void Tick(float DeltaTime) override;
	virtual bool ShouldTickIfViewportsOnly() const override;

	//** EXTERNAL GAME FUNCTIONS **/

	//Movement
	UFUNCTION(BlueprintCallable, Category = "Gameplay Functions")
	void MoveToRandomPosition();
	//Context Updating
	UFUNCTION(BlueprintCallable, Category = "Gameplay Functions")
	void UpdateUnitContext();
	//Fighting
	UFUNCTION(BlueprintCallable, Category = "Gameplay Functions")
	void SimulateFightFromCurrentContext();
};