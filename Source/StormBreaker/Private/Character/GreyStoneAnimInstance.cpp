// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GreyStoneAnimInstance.h"
#include "Character/GreyStoneCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"


//Acts like tick for animation & Get Speed.
void UGreyStoneAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (GreyStoneCharacter == nullptr)
	{
		GreyStoneCharacter = Cast<AGreyStoneCharacter>(TryGetPawnOwner());
		
	}

	if (GreyStoneCharacter)
	{
		//Get Speed of Main Character from velocity
		FVector Velocity{ GreyStoneCharacter->GetVelocity() };
		Velocity.Z = 0;
		Speed = Velocity.Size();

		//is the player in air
		bIsInAir = GreyStoneCharacter->GetCharacterMovement()->IsFalling();

		//Get Offset yaw to user in blen spaces
		FRotator const AimRotation = GreyStoneCharacter->GetBaseAimRotation();
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(GreyStoneCharacter->GetVelocity());

		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
	}
}

// Acts like begin play create reference to Charater
void UGreyStoneAnimInstance::NativeInitializeAnimation()
{

	GreyStoneCharacter = Cast<AGreyStoneCharacter>(TryGetPawnOwner());


}
