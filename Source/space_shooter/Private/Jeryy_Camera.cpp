// Fill out your copyright notice in the Description page of Project Settings.


#include "Jeryy_Camera.h"

// Sets default values
AJeryy_Camera::AJeryy_Camera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJeryy_Camera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJeryy_Camera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJeryy_Camera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

