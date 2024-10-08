// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GreyStoneCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemy/MeleeHitInterface.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGreyStoneCharacter::AGreyStoneCharacter() :
	DefaultTurnRate(45.f),
	DefaultLookupRate(45.f),
	WalkSpeed(300.f),
	RunningSpeed(600.f),
	BaseDamage(20.f)
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

	// Setup pitch Yaw Roll
	bUseControllerRotationPitch			= false;
	bUseControllerRotationYaw			= true;
	bUseControllerRotationRoll			= false;

	//configure character movements
	// Zero Pitch and roll only rotate in yaw direction

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);

	//Jumping
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.1f;

	//Right weapon Collision box

	RightWeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Weapon Box"));
	RightWeaponCollision->SetupAttachment(GetMesh(), FName("RightWeaponBone"));

}

// Called when the game starts or when spawned
void AGreyStoneCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Bind Function to overlap event for weapon box
	RightWeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AGreyStoneCharacter::OnRightWeaponOverlap);


	//Setup right Weapon collision box
	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightWeaponCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	RightWeaponCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RightWeaponCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
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

void AGreyStoneCharacter::StopRunning()
{
	if (GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.0f)
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}

void AGreyStoneCharacter::Running()
{
	GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
}

void AGreyStoneCharacter::Recall()
{
	PlayAnimMontage(RecallMontage, FName("Recall"));
}

//Play anim montage that disable character movement
void AGreyStoneCharacter::PlayAnimMontage(UAnimMontage* MontageToPlay, FName SectionName)
{

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && MontageToPlay)
	{
		//Disable Character Movement
		GetCharacterMovement()->DisableMovement();

		//Get time it takes to play montage
		int32 const SectionIndex = MontageToPlay->GetSectionIndex(SectionName);
		int32 const SectionLength = MontageToPlay->GetSectionLength(SectionIndex);

		//Play montage and start timer
		AnimInstance->Montage_Play(MontageToPlay);
		AnimInstance->Montage_JumpToSection(SectionName);

		//Setup timer to enable walking after montage stop playing
		GetWorldTimerManager().SetTimer(TimerMovementWaling, this, &AGreyStoneCharacter::EnableWalk, SectionLength);
	}

}

void AGreyStoneCharacter::EnableWalk()
{
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void AGreyStoneCharacter::MainAttack()
{

	PlayAnimMontage(MainAttackMontage, FName("MainAttack"));

}

void AGreyStoneCharacter::OnRightWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	/*IMeleeHitInterface* MeleeHitInterface = Cast<IMeleeHitInterface>(SweepResult.GetActor());

	if (MeleeHitInterface)
	{
		MeleeHitInterface->MeleeHIt_Implementation(SweepResult);
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Apply damage"));*/

	if (IsValid(SweepResult.GetActor()))
	{
		IMeleeHitInterface* MeleeHitInterface = Cast<IMeleeHitInterface>(SweepResult.GetActor());

		if (MeleeHitInterface)
		{
			MeleeHitInterface->MeleeHIt_Implementation(SweepResult);
		}
		// Apply damage to enemy
		UGameplayStatics::ApplyDamage(
			SweepResult.GetActor(),
			BaseDamage,
			GetController(),
			this,
			UDamageType::StaticClass());
	}

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

		// Jumping
		PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
		PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

		//Running

		PlayerInputComponent->BindAction("Running", IE_Pressed, this, &AGreyStoneCharacter::Running);
		PlayerInputComponent->BindAction("Running", IE_Released, this, &AGreyStoneCharacter::StopRunning);

		//Cobact Abilities
		PlayerInputComponent->BindAction("Recall", IE_Pressed, this, &AGreyStoneCharacter::Recall);
		
		//Attack
		PlayerInputComponent->BindAction("MainAttack", IE_Pressed, this, &AGreyStoneCharacter::MainAttack);

}

void AGreyStoneCharacter::ActivateRightWeapon()
{

	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

}

void AGreyStoneCharacter::DeactivateRightWeapon()
{

	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

