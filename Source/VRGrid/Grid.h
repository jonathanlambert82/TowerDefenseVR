// Fill out your copyright notice in the Description page of Project Settings.

//The Grid actor is the base of the play area. It can be moved by the player and is used as a positional reference for all of the other actors.

#pragma once

#include "GameFramework/Actor.h"
#include "NavPoint.h"
#include "MotionControllerComponent.h"

#include "Grid.generated.h"

UCLASS()
class VRGRID_API AGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrid();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

#pragma region Variables
	//Variables
	UPROPERTY( EditAnywhere, meta = (ClampMin = "3", ClampMax = "500"))
	int gridUnits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NavPoints", Meta = (MakeEditWidget = true))
		FVector enemySpawnPoint;
			
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NavPoints", Meta = (MakeEditWidget = true))
	TArray<FVector> navPoints;

	UPROPERTY(BlueprintReadWrite, Category = "NavPoints")
	TArray<ANavPoint*> navPointActors;

	int numNavPoints;
			
	TArray<FVector> gridPoints;
		
	FVector boundsExtent;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "1", ClampMax = "20"))
	int gridUnitSize;

	UPROPERTY(EditAnywhere)
	UInstancedStaticMeshComponent* instancedStaticMeshComponent;
	
	USceneComponent* gridRoot;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* gridMeshComponent;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* dislpayMeshComponent;

#pragma endregion


#pragma region Functions
	//Functions
	void GenerateGrid(int, FVector, int);

	UFUNCTION(BlueprintCallable, Category = "Grid")
		FVector GetExtents();

	UFUNCTION(BlueprintCallable, Category = "Grid")
		int GetNumGridUnits() { return gridUnits; }


	UFUNCTION(BlueprintCallable, Category = "Grid")
		void MoveGrid(FVector offset, UMotionControllerComponent* controllerComponent);
		

	UFUNCTION(BlueprintCallable, Category = "NavPoints")
		FVector GetNavPoint(int index);

	UFUNCTION(BlueprintCallable, Category = "NavPoints")
		void SetNavPoints();

#pragma endregion
};
