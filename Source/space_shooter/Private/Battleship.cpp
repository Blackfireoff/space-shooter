// Fill out your copyright notice in the Description page of Project Settings.


#include "Battleship.h"

#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h" // Added for camera boom
#include "Camera/CameraComponent.h"          // Added for camera
#include "GameFramework/FloatingPawnMovement.h" // Movement
#include "EnhancedInputComponent.h"             // Enhanced input binding
#include "EnhancedInputSubsystems.h"            // Mapping context subsystem
#include "InputActionValue.h"                   // FInputActionValue

// Sets default values
ABattleship::ABattleship()
{
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

    MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));

    // Possess this pawn by default so camera follows the battleship
    AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ABattleship::BeginPlay()
{
    Super::BeginPlay();
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (ULocalPlayer* LP = PC->GetLocalPlayer())
        {
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LP))
            {
                if (DefaultMappingContext)
                {
                    Subsystem->AddMappingContext(DefaultMappingContext, 0);
                }
            }
        }
    }
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
    if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (MoveAction)
        {
            EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABattleship::Move);
            EIC->BindAction(MoveAction, ETriggerEvent::Completed, this, &ABattleship::Move); // Zero input on release
        }
    }
}

void ABattleship::Move(const FInputActionValue& Value)
{
    // Expecting a 2D Vector from the Enhanced Input Action (X = Forward, Y = Right)
    const FVector2D Input = Value.Get<FVector2D>();
    if (!Controller || Input.IsNearlyZero())
    {
        return;
    }
    // Move only in world X (forward) and Y (right) plane, ignore Z.
    if (Input.X != 0.f)
    {
        AddMovementInput(FVector::ForwardVector, Input.X);
    }
    if (Input.Y != 0.f)
    {
        AddMovementInput(FVector::RightVector, Input.Y);
    }
}

UPawnMovementComponent* ABattleship::GetMovementComponent() const
{
    return MovementComponent;
}
