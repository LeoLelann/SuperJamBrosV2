#pragma once

#include "CoreMinimal.h"
#include "SmashCharacterSettings.h"
#include "SmashCharacterStateID.h"
#include "Components/ActorComponent.h"
#include "SmashCharacterState.generated.h"


class ASmashCharacter;
class USmashCharacterStateMachine;
class UAnimMontage;

UCLASS (abstract)
class SMASHUE_API USmashCharacterState : public UActorComponent
{
	GENERATED_BODY()

public:
	USmashCharacterState();

	virtual ESmashCharacterStateID GetStateID();
	virtual void StateInit(USmashCharacterStateMachine* InStateMachine);
	virtual void StateEnter(ESmashCharacterStateID PreviousStateID);
	virtual void StateExit(ESmashCharacterStateID NextStateID);

	virtual void StateTick(float DeltaTime);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Anims")
	UAnimMontage* AnimMontage;

protected:
	UPROPERTY()
	TObjectPtr<ASmashCharacter> Character;

	UPROPERTY()
	TObjectPtr<USmashCharacterStateMachine> StateMachine;

	UPROPERTY()
	const USmashCharacterSettings* CharacterSettings;
};


enum class EArenaPlayerOrient : uint8
{
	Left,
	Right
};
