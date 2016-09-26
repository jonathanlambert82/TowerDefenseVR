// Fill out your copyright notice in the Description page of Project Settings.

#include "VRGrid.h"
#include "Grid.h"


// Sets default values
AGrid::AGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set Root
	gridRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	if (RootComponent == nullptr)
	{
		RootComponent = gridRoot;
	}
	else
	{
		gridRoot->AttachTo(RootComponent);
	}

	
	
	//Setup Meshes
	gridMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grid Mesh"));
	
	gridMeshComponent->AttachTo(RootComponent);

	dislpayMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Display Mesh"));

	dislpayMeshComponent->AttachTo(RootComponent);

	instancedStaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("ismc"));
		
	instancedStaticMeshComponent->AttachTo(RootComponent);

	

}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();

	GenerateGrid(gridUnits,GetActorLocation(), gridUnitSize);

	SetNavPoints();
		
}

// Called every frame
void AGrid::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	
}


//Set up the grid. 2d array based on the size and spacing specified in the editor
void AGrid::GenerateGrid(int Units, FVector origin, int unitSize)
{
	FVector currentPoint(0.0f, 0.0f, 0.0f);
		
	//Calculate gridpoints
	for (int y = 0; y < Units; y++)
	{
	
		for (int x = 0; x < Units; x++)
		{
			gridPoints.Emplace(FVector(currentPoint.X, currentPoint.Y, 0.0f));

			currentPoint.X += gridUnitSize;

		}

		currentPoint.Y += gridUnitSize;
		currentPoint.X = 0;

	}

	
	//Center Grid to Root
	float halfGridSize = (Units / 2) * gridUnitSize;

	for (int i = 0; i < gridPoints.Num(); i++)
	{
		
		gridPoints[i] = FVector(gridPoints[i].X - halfGridSize, gridPoints[i].Y - halfGridSize, 0.0f);

	}

	//Add sphere collision at points
	for (int i = 0; i < gridPoints.Num(); i++)
	{
		
		USphereComponent* newComponent = NewObject<USphereComponent>(this);
		newComponent->RegisterComponentWithWorld(GetWorld());
		newComponent->AttachTo(RootComponent);
		newComponent->SetSphereRadius(gridUnitSize/4.0f, true);
		newComponent->SetRelativeLocation(FVector(gridPoints[i].X, gridPoints[i].Y, gridPoints[i].Z));
		newComponent->SetCollisionObjectType(ECC_GameTraceChannel1);
		newComponent->bGenerateOverlapEvents = true;
	}

	//Scale GridMesh to fit 
	gridMeshComponent->SetWorldScale3D(FVector(gridUnitSize*gridUnits, gridUnitSize*gridUnits, 1.0f));
	
}


//Get the size of the playable area. The size can be set in the editor.
FVector AGrid::GetExtents()
{
	FVector extents;
	extents = FVector(sqrt(gridPoints.Num()) * (gridUnitSize * 0.5f), sqrt(gridPoints.Num()) * (gridUnitSize * 0.5f) ,16.0f);

	return extents;
}

void AGrid::MoveGrid(FVector offset, UMotionControllerComponent* controllerComponent)
{
	SetActorLocation(offset + controllerComponent->GetComponentLocation());
	
}


FVector AGrid::GetNavPoint(int index)
{
	return navPoints[index];
}



/*Spawn and attatch navigation point actors at the locations specified in the editor. These are used by spawned enemies to navigate to the 
goal point.*/
void AGrid::SetNavPoints()
{
	UWorld* const World = GetWorld();
		
	//All of the Navigation point objects will be spawned relative to the grid object.
	FVector GridWorldPosition = GetActorLocation();
	
	for (int i = 0; i < navPoints.Num(); i++)
	{
		
		if (World)
		{
			ANavPoint* temp = World->SpawnActor<ANavPoint>();
			temp->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

			//navPoints are relative to the grid actor, so we need to add the grid's position to get the correct location in world space
			temp->SetActorLocation(navPoints[i] + GridWorldPosition);
			navPointActors.Add(temp);
		}
		
	}
	
	
}

