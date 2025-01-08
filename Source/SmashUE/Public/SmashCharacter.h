
#pragma once
#include "CoreMinimal.h"
#include "CameraFollowTarget.h"
#include "GameFramework/Character.h"
#include "SmashCharacter.generated.h"

UCLASS()
class SMASHUE_API ASmashCharacter : public ACharacter,
									public ICameraFollowTarget
{
	GENERATED_BODY()

#pragma region Unreal Default

public:
	// Sets default values for this character's properties
	ASmashCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma endregion

#pragma region Orient

public:
	float GetOrientX() const;
	void SetOrientX(float NewOrientX);

protected:
	UPROPERTY(BlueprintReadOnly)
	float OrientX = 1.0f;

	void RotateMeshUsingOrientX() const;
#pragma endregion

	
#pragma region StateMachine

public:
	void CreateStateMachine();
	
	void InitStateMachine();

	void TickStateMachine(float DeltaTime) const;
	
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class USmashCharacterStateMachine> StateMachine;

#pragma endregion

#pragma region Input Data / Mapping Context

public:
	UPROPERTY()
	TObjectPtr<class UInputMappingContext> InputMappingContext;
	UPROPERTY()
	TObjectPtr<class USmashCharachterInputData> InputData;
	UPROPERTY()
	TObjectPtr<class UEnhancedInputLocalPlayerSubsystem> InputSystem;

protected:
	void SetupMappingContextIntoController();

#pragma endregion

#pragma region input Move X

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputMoveXEvent, float, InputMoveX);
	
public:
	float GetInputMoveX() const;

	UPROPERTY()
	FInputMoveXEvent InputMoveXFastEvent;
	
protected:
	UPROPERTY()
	float InputMoveX = 0.0f;

private:
	void BindInputMoveXAxisAndActions(UEnhancedInputComponent* EnhancedInputComponent);

	void OnInputMoveX(const FInputActionValue& InputActionValue);

	void OnInputMoveXFast(const ::FInputActionValue& InputActionValue);


#pragma endregion

#pragma region Camera Target

public:
	virtual FVector GetFollowPosition() override;
    virtual bool IsFollowable() override;
	
#pragma endregion
};
