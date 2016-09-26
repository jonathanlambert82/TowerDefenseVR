// Fill out your copyright notice in the Description page of Project Settings.

/*Placeable is the base class for all actors that can be placed on the level grid or moved by the player.
Placeables always snap to the grid after being placed. */


#pragma once

#include "GameFramework/Actor.h"
#include "MotionControllerComponent.h"
#include "Placeable.generated.h"


UCLASS()
class VRGRID_API APlaceable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlaceable();


	//Variables
	USceneComponent* root;

	USphereComponent* snapComponent;

	UPROPERTY(BlueprintReadWrite)
	bool bShouldSnap;
		
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* staticMeshComponent;

	
	//Functions
	UFUNCTION(BlueprintCallable, Category = "Placeable")
		void GrabPlaceable(UMotionControllerComponent* motionController);
	
	UFUNCTION(BlueprintCallable, Category = "Placeable")
		void ReleasePlaceable();

	UFUNCTION(BlueprintCallable, Category = "Placeable")
		void SetSnapComponent(USphereComponent * snapComp);
	
	UFUNCTION(BlueprintCallable, Category = "Placeable")
		void Snap(USphereComponent* snapPoint);
	
	

	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
