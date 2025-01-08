#include "SmashCharacterStateRun.h"
#include "SmashCharacter.h"
#include "SmashCharacterStateMachine.h"

ESmashCharacterStateID USmashCharacterStateRun::GetStateID()
{
	return ESmashCharacterStateID::Run;
}

void USmashCharacterStateRun::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);

	Character = Cast<ASmashCharacter>(GetOwner());

	if (!Character)
	{
		return;
	}
	
	GEngine -> AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Enter StateRun"));
	Character->PlayAnimMontage(AnimMontage);
}

void USmashCharacterStateRun::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);

	GEngine -> AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Exit StateRun"));
}

void USmashCharacterStateRun::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);

	if (FMath::Abs(Character->GetInputMoveX()) < CharacterSettings->InputMoveXThreshold)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Idle);
	}
	else
	{
		Character->SetOrientX(Character->GetInputMoveX());
		Character->AddMovementInput(FVector::ForwardVector, Character->GetOrientX());
	}
	Run();
}

void USmashCharacterStateRun::Run()
{
	//if (!Character)
	//{
	//	return;
	//}
//
	//FVector MoveOffset;
	//if (!Character->GetInputMoveX() && MoveOffset.X == 0)
	//{
	//	StateMachine->ChangeState(ESmashCharacterStateID::Idle);
	//}
	//else if (!Character->GetInputMoveX())
	//{
	//	MoveOffset.X = 0;
	//}
	//else if (Character->GetInputMoveX())
	//{
	//	//FVector MoveOffset = FVector::ZeroVector;
	//	MoveOffset.X = MoveDirection * WalkSpeed * GetWorld()->GetDeltaSeconds();
	//	Character->AddActorWorldOffset(MoveOffset, true);
	//}
}
