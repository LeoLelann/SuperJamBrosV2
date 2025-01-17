#pragma once
#include "CoreMinimal.h"
#include "SmashCharacterState.h"
#include "SmashCharacterStateRun.generated.h"

UCLASS(ClassGroup=(SmashCharacterState), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashCharacterStateRun : public USmashCharacterState
{
	GENERATED_BODY()
	
public:
	
	virtual ESmashCharacterStateID GetStateID() override;
	virtual void StateEnter(ESmashCharacterStateID PreviousStateID) override;
	virtual void StateExit(ESmashCharacterStateID NextStateID) override;

	virtual void StateTick(float DeltaTime) override;
	void Run();
	
	//UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Anims")
	//UAnimMontage* RunMontage;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WalkSpeed")
	float WalkSpeed;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Movement")
	float MoveDirection = 1.0f;
};
