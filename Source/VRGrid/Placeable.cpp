// Fill out your copyright notice in the Description page of Project Settings.

#include "VRGrid.h"
#include "Placeable.h"



// Sets default values
APlaceable::APlaceable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set Root
	

	if (RootComponent == nullptr)
	{
		RootComponent = root;
	}
	else
	{
		root->AttachTo(RootComponent);
	}

	staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	staticMeshComponent->bGenerateOverlapEvents = true;

	bShouldSnap = false;
}

// Called when the game starts or when spawned
void APlaceable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlaceable::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void APlaceable::Snap(USphereComponent* snapComponent)
{
	if (snapComponent != nullptr)
	{
		AttachRootComponentTo(snapComponent);
		SetActorLocation(snapComponent->GetComponentLocation());
		SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));

	}
		
}


void APlaceable::GrabPlaceable(UMotionControllerComponent* motionController)
{
	AttachToComponent(motionController, FAttachmentTransformRules::KeepWorldTransform);
	
}


void APlaceable::ReleasePlaceable()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	
	if (bShouldSnap && IsValid(snapComponent ))
	{
		Snap(snapComponent);
	}
	else
	{
		Destroy();
	}
}


void APlaceable::SetSnapComponent(USphereComponent* snapComp)
{
	snapComponent = snapComp;
}