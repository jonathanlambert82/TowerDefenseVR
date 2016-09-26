// Fill out your copyright notice in the Description page of Project Settings.

#include "VRGrid.h"
#include "NavPoint.h"


// Sets default values
ANavPoint::ANavPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComp;	
		
}

// Called when the game starts or when spawned
void ANavPoint::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComp->SetSphereRadius(5.0f, true);
	
	SphereComp->bHiddenInGame = false;
}

// Called every frame
void ANavPoint::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

