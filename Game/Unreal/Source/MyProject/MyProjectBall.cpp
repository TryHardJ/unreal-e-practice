// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProjectBall.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Components/CapsuleComponent.h"
#include "Engine.h"
#include "MyActor2.h"

AMyProjectBall::AMyProjectBall()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BallMesh(TEXT("/Game/Rolling/Meshes/BallMesh.BallMesh"));

	/*FTimerHandle TimerHandle; // Thinking about adding a timer
	GetWorldTimerManager().SetTimer(TimerHandle, this, 
		&AMyProjectBall::CountDown, 1.f, true, 0.0);  // this means pointer in the current class, rate is 1, we want it to loop, first delay will be 0 because we want it to be instant*/

	// Create mesh component for the ball
	Ball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball0"));
	Ball->SetStaticMesh(BallMesh.Object);
	Ball->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	Ball->SetSimulatePhysics(true);
	Ball->SetAngularDamping(0.1f);
	Ball->SetLinearDamping(0.1f);
	Ball->BodyInstance.MassScale = 3.5f;
	Ball->BodyInstance.MaxAngularVelocity = 800.0f;
	Ball->SetNotifyRigidBodyCollision(true);
	Ball->SetGenerateOverlapEvents(true);

	// AddDynamic Macro allows Ball(UProperty) to bind with OnOverlapBegin(UFunction)
	Ball->OnComponentBeginOverlap.AddDynamic(this, &AMyProjectBall::OnOverlapBegin);

	RootComponent = Ball;

	// Create a camera boom attached to the root (ball)
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetUsingAbsoluteRotation(true); // Rotation of the ball should not affect rotation of boom
	SpringArm->SetRelativeRotation(FRotator(-10.f, 0.f, 0.f)); //Pitch is the spring arm view, 90 would give it an over the top view
	SpringArm->TargetArmLength = 1200.f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 3.f;

	// Create a camera and attach to boom
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	tempPos = GetActorLocation(); // get the current actor location
	tempPos.X -= 850.0f; // - 850 from the x position
	tempPos.Z += 300.0f; // adding 300 to the z position of tempPos
	Camera->SetWorldLocation(tempPos);  // set position to world location of camera

	// Set up forces
	RollTorque = 50000000.0f; //50000000.0f
	JumpImpulse = 350000.0f; //350000.0f
	bCanJump = true; // Start being able to jump
}


void AMyProjectBall::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName())); //  get the name of the world we are in and open it from the start
}

void AMyProjectBall::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr) // if we hit something
	{
		AMyActor2* DeadZone = Cast<AMyActor2>(OtherActor);  // cast the parameter OtherActor to the AMyActor2 which = spikes or deadzone

		if (DeadZone)
		{
			Ball->Deactivate();
			Ball->SetVisibility(false);
			CanMove = false;

			FTimerHandle UnusedHandle; // First step to restarting level, not using it but need to call it
			GetWorldTimerManager().SetTimer(UnusedHandle, this,
				&AMyProjectBall::RestartLevel, 0.5f, false); // this class = AMy..RestartLevel call that function after 2 seconds and false means not to repeat over and over again
		}
	}
}


void AMyProjectBall::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyProjectBall::MoveRight);
	PlayerInputComponent->BindAxis("MoveLeft", this, &AMyProjectBall::MoveLeft);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyProjectBall::MoveForward);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyProjectBall::Jump);
}

void AMyProjectBall::MoveRight(float Val)
{
	const FVector Torque = FVector(-1.f * Val * RollTorque, 0.f, 0.f);
	Ball->AddTorqueInRadians(Torque);
}

void AMyProjectBall::MoveLeft(float Val)
{
	const FVector Torque = FVector(1.f * Val * RollTorque, 0.f, 0.f);
	Ball->AddTorqueInRadians(Torque);
}

void AMyProjectBall::MoveForward(float Val)
{
	const FVector Torque = FVector(20.f, Val * RollTorque, 0.f);
	Ball->AddTorqueInRadians(Torque);
	
}

void AMyProjectBall::Jump()
{
	if(bCanJump)
	{
		const FVector Impulse = FVector(0.f, 0.f, JumpImpulse);
		Ball->AddImpulse(Impulse);
		bCanJump = false;
	}
}

void AMyProjectBall::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	bCanJump = true;
}



