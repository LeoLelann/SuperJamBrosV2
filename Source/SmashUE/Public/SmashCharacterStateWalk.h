// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmashCharacterState.h"
#include "Arena/ArenaPlayerStart.h"
#include "SmashCharacterStateWalk.generated.h"

enum class EArenaPlayerStartOrient : uint8;

UCLASS(ClassGroup=(SmashCharacterState), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashCharacterStateWalk : public USmashCharacterState
{
	GENERATED_BODY()
	
public:
	
	virtual ESmashCharacterStateID GetStateID() override;
	virtual void StateEnter(ESmashCharacterStateID PreviousStateID) override;
	virtual void StateExit(ESmashCharacterStateID NextStateID) override;

	virtual void StateTick(float DeltaTime) override;
	void Move();

	UFUNCTION()
	void OnInputMoveXFast(float InputMoveX);

	//UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Anims")
	//UAnimMontage* WalkMontage;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WalkSpeed")
	float WalkSpeed =200.f;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Movement")
	float MoveDirection = 1.0f;

	EArenaPlayerOrient PlayerOrient;
};
