// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmashCharacterState.h"
#include "SmashCharacterStateIdle.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(SmashCharacterState), meta=(BlueprintSpawnableComponent))
class USmashCharacterStateIdle : public USmashCharacterState
{
	GENERATED_BODY()

public:
	virtual ESmashCharacterStateID GetStateID() override;
	
	UFUNCTION()
	virtual void StateEnter(ESmashCharacterStateID PreviousStateID) override;
	virtual void StateExit(ESmashCharacterStateID NextStateID) override;
	virtual void StateTick(float DeltaTime) override;

	UFUNCTION()
	void OnInputMoveXFast(float InputMoveX);
};
