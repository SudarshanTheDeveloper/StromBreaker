// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GreyStoneCharacter.generated.h"

//Declaration

class USpringArmComponent;
class UCameraComponent;
class UAnimMontage;

UCLASS()
class STORMBREAKER_API AGreyStoneCharacter : public ACharacter//, public IGrayStoneCharacterInterface 
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGreyStoneCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// Activate and Deactivate WeaponBoxes
	virtual void ActivateRightWeapon();
	virtual void DeactivateRightWeapon();

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


	//Stop and running
	void StopRunning();
	
	void Running();

	//Recal ability
	void Recall();

	//Play animation montage that disable movements
	void PlayAnimMontage(UAnimMontage* MontageToPlay, FName SectionName = "Default");


	// Set Character movement back to walking state.
	void EnableWalk();

	//LMB Main Attack
	void MainAttack();


	//RightWeapon overlap
	UFUNCTION()
	void OnRightWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


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

	// Set walk speed
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float WalkSpeed;

	// Set run speed
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RunningSpeed;

	//Disable Movement While Montage is played
	FTimerHandle TimerMovementWaling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* RecallMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* MainAttackMontage;
	//Right weapon Collision
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* RightWeaponCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float BaseDamage;
};
