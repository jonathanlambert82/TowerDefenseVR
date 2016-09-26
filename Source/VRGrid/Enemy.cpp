// Fill out your copyright notice in the Description page of Project Settings.

#include "VRGrid.h"
#include "Enemy.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
			
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	RootComponent = Root;

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	SkeletalMeshComp->SetupAttachment(RootComponent);
	
	Sphere->SetupAttachment(RootComponent);

	currentNavPointIndex = 0;
		
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{

	Super::BeginPlay();
		
	Sphere->SetSphereRadius(5.0f, true);
		
}

// Called every frame
void AEnemy::Tick( float DeltaTime )
{

	Super::Tick( DeltaTime );

	if (bAttacking)
	{

		Move();	

	}

}

void AEnemy::Move()
{

	moveVector =  RootComponent->GetForwardVector() * (speed * FApp::GetDeltaTime());  

	RootComponent->AddWorldOffset(moveVector, false);
	
}

void AEnemy::SetNextWayPoint()
{

	if (grid != nullptr && currentNavPointIndex < grid->navPoints.Num() - 1)
	{

		currentNavPointIndex++;

	}
	else
		Destroy();

}

