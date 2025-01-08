
#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "SmashCharachterInputData.h"
#include "SmashCharacterSettings.h"
#include "GameFramework/GameModeBase.h"
#include "MatchGameMode.generated.h"

class AArenaPlayerStart;
class ASmashCharacter;


UCLASS()
class SMASHUE_API AMatchGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	TArray<ASmashCharacter*> CharactersInsideArena;
	
	//UPROPERTY(EditAnywhere)
	//TSubclassOf<ASmashCharacter> SmashCharacterClassP0;
//
	//UPROPERTY(EditAnywhere)
	//TSubclassOf<ASmashCharacter> SmashCharacterClassP1;
//
	//UPROPERTY(EditAnywhere)
	//TSubclassOf<ASmashCharacter> SmashCharacterClassP2;
//
	//UPROPERTY(EditAnywhere)
	//TSubclassOf<ASmashCharacter> SmashCharacterClassP3;
	
private:
	void FindPlayerStartActorsInArena(TArray<AArenaPlayerStart*>& ResultActors);

	TSubclassOf<ASmashCharacter> GetSmashCharacterClassFromInputType(EAutoReceiveInput::Type InputType) const;

	void SpawnCharacters(const TArray<AArenaPlayerStart*>& SpawnPoints);

	USmashCharachterInputData* LoadInputDataFromConfig();

	UInputMappingContext* LoadInputMappingContextFromConfig();
};
