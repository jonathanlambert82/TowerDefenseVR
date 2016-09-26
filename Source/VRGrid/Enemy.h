// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/KismetMathLibrary.h"
#include "Grid.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"


UCLASS()
class VRGRID_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


#pragma region Variables
	
	UPROPERTY(BlueprintReadWrite)
	USphereComponent* Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
			
	FVector moveVector;

	UPROPERTY(BlueprintReadWrite)
		float speed = 10.0f;

	UPROPERTY(BlueprintReadWrite)
		int health;

	UPROPERTY(BlueprintReadWrite)
		int damage;

	UPROPERTY(BlueprintReadWrite)
		int currentNavPointIndex;

	UPROPERTY(BlueprintReadWrite)
		FRotator newRotation;

	UPROPERTY(BlueprintReadWrite)
		AGrid* grid;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USkeletalMeshComponent* SkeletalMeshComp;

	UPROPERTY(BlueprintReadWrite)
		UArrowComponent* arrow;

	UPROPERTY(BlueprintReadWrite)
		bool bAttacking = false;

	


#pragma endregion 

#pragma region Functions

	UFUNCTION(BlueprintCallable, Category = "Enemy")
		void Move();

	UFUNCTION(BlueprintCallable, Category = "Enemy")
		void SetNextWayPoint();

	

#pragma endregion
};
