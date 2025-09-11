// Fill out your copyright notice in the Description page of Project Settings.


#include "Battleship.h"

#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h" // Added for camera boom
#include "Camera/CameraComponent.h"          // Added for camera

// Sets default values
ABattleship::ABattleship()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Create BoxComponent and set as RootComponent for the Actor
    BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
    RootComponent = BoxCollision;

    // Create StaticMeshComponent and Attach to BoxComponent
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMesh->SetupAttachment(BoxCollision);

    // Create SpringArm (camera boom)
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    // Intentionally NOT setting TargetArmLength, rotation, or collision test here; configure in Blueprint.

    // Create Camera
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false;

    // Possess this pawn by default so camera follows the battleship
    AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ABattleship::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void ABattleship::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABattleship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}
