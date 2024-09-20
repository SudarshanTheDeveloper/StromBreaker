// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GreyStoneAnimInstance.h"
#include "Character/GreyStoneCharacter.h"


//Acts like tick for animation & Get Speed.
void UGreyStoneAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (GreyStoneCharacter == nullptr)
	{
		GreyStoneCharacter = Cast<AGreyStoneCharacter>(TryGetPawnOwner());
		
	}

	if (GreyStoneCharacter)
	{
		FVector Velocity{ GreyStoneCharacter->GetVelocity() };
		Velocity.Z = 0;
		Speed = Velocity.Size();
	}
}

// Acts like begin play create reference to Charater
void UGreyStoneAnimInstance::NativeInitializeAnimation()
{

	GreyStoneCharacter = Cast<AGreyStoneCharacter>(TryGetPawnOwner());


}
