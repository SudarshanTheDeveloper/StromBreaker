// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GreyStoneCharacter.h"
#include "GreyStoneAnimInstance.generated.h"

//Declaration
class AGrayStoneCharater;

/**
 * 
 */
UCLASS()
class STORMBREAKER_API UGreyStoneAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	//Used In animation Blueprint
	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);

	//We can Initialize our own variable and be able to use them in BP
	virtual void NativeInitializeAnimation() override;


	//Create Variable to have reference to Wukong character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	AGreyStoneCharacter* GreyStoneCharacter;


	//Speed of GrayStoneCharacter
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float Speed;

	// Checking Player in air or not
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsInAir;

	//Offset of GrayStoneCharacter
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float MovementOffsetYaw;
};
