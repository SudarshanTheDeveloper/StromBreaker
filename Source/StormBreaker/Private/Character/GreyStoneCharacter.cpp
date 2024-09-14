// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GreyStoneCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AGreyStoneCharacter::AGreyStoneCharacter() :
	DefaultTurnRate(45.f),
	DefaultLookupRate(45.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	//Creating Springarm Component
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 300.f;
	SpringArmComponent->bUsePawnControlRotation = true;

	//create camera component
	FollowCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	FollowCameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	FollowCameraComponent->bUsePawnControlRotation = false;

}

// Called when the game starts or when spawned
void AGreyStoneCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGreyStoneCharacter::MoveForward(float Value)
{
	if((Controller != nullptr) && (Value !=0.f))
	{
		const FRotator Rotation{ Controller->GetControlRotation() };


		const FRotator YawRotation{ 0, Rotation.Yaw, 0};

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X) };

		AddMovementInput(Direction, Value);
	}

	else 
	{
		UE_LOG(LogTemp,Warning,TEXT("Move Forward Function Not working"))
	}

}

void AGreyStoneCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.f))
	{
		const FRotator Rotation{ Controller->GetControlRotation() };


		const FRotator YawRotation{ 0, Rotation.Yaw, 0 };

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y) };

		AddMovementInput(Direction, Value);
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Move Right Function Not working"))
	}
}

void AGreyStoneCharacter::TurnRate(float Rate)
{
	// Turning Degrees per delta seconds
	AddControllerYawInput(Rate * DefaultTurnRate * GetWorld()->GetDeltaSeconds());

}

void AGreyStoneCharacter::LookUpRate(float Rate)
{
	//Lookup rate degrees per delta seconds
	AddControllerPitchInput(Rate * DefaultLookupRate * GetWorld()->GetDeltaSeconds());

}

// Called to bind functionality to input
void AGreyStoneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Make Sure component is valid
	check(PlayerInputComponent)

		//Player movement
		PlayerInputComponent->BindAxis("MoveForward", this, &AGreyStoneCharacter::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &AGreyStoneCharacter::MoveRight);
		PlayerInputComponent->BindAxis("TurnRate", this, &AGreyStoneCharacter::TurnRate);
		PlayerInputComponent->BindAxis("LookUpRate", this, &AGreyStoneCharacter::LookUpRate);
		PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
		PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

}

