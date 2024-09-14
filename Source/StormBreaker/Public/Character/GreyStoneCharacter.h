// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "GreyStoneCharacter.generated.h"

//Declaration

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class STORMBREAKER_API AGreyStoneCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGreyStoneCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//This will work for moving forward and backwards
	void MoveForward(float Value);

	//this will work for moving right and left
	void MoveRight(float Value);

	//Input to turn at normalaize rate given
	void TurnRate(float Rate);

	//Input to lookUp or down at notamalize rate given
	void LookUpRate(float Rate);

private:

	//Spring Arm Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Camera", meta=(AllowPrivateAccess="true"))
	USpringArmComponent* SpringArmComponent;

	//Follow Camera Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCameraComponent;

	//Default Turn rate
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float DefaultTurnRate;

	//Default Lookup Rate
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float DefaultLookupRate;
};
