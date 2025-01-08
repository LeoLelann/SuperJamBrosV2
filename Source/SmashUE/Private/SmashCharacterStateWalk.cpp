#include "SmashCharacterStateWalk.h"

#include "Editor.h"
#include "SmashCharacter.h"
#include "SmashCharacterStateMachine.h"

ESmashCharacterStateID USmashCharacterStateWalk::GetStateID()
{
	return ESmashCharacterStateID::Walk;
}

void USmashCharacterStateWalk::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);

	Character = Cast<ASmashCharacter>(GetOwner());

	if (!Character)
	{
		return;
	}
	Character->PlayAnimMontage(AnimMontage);

	Character->InputMoveXFastEvent.AddDynamic(this, &USmashCharacterStateWalk::OnInputMoveXFast);
}

void USmashCharacterStateWalk::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);

	Character->InputMoveXFastEvent.RemoveDynamic(this, &USmashCharacterStateWalk::OnInputMoveXFast);
}

void USmashCharacterStateWalk::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	GEngine -> AddOnScreenDebugMessage(-1, 0.1f, FColor::Cyan, TEXT("Tick StateWalk"));
	
	Move();
	
	if (FMath::Abs(Character->GetInputMoveX()) < 0.1f && Character->GetInputMoveX() > -0.1f)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Idle);
	}
	else
	{
		Character->SetOrientX(Character->GetInputMoveX());
		Character->AddMovementInput(FVector::ForwardVector, Character->GetOrientX());
	}
}

void USmashCharacterStateWalk::Move()
{
	if (!Character)
	{
		return;
	}

	FVector MoveOffset = FVector::ZeroVector;
	MoveOffset.X = MoveDirection * WalkSpeed * GetWorld()->GetDeltaSeconds();

	Character->AddActorWorldOffset(MoveOffset, true);
}

void USmashCharacterStateWalk::OnInputMoveXFast(float InputMoveX)
{
	StateMachine->ChangeState(ESmashCharacterStateID::Run);
}