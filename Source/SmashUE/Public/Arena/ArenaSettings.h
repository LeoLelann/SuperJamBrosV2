#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ArenaSettings.generated.h"

class ASmashCharacter;

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Smash Arena Settings"))
class SMASHUE_API UArenaSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(config, EditAnywhere, category = "Characters")
	TSubclassOf<ASmashCharacter> SmashCharacterClassP0;

	UPROPERTY(config, EditAnywhere, category = "Characters")
	TSubclassOf<ASmashCharacter> SmashCharacterClassP1;

	UPROPERTY(config, EditAnywhere, category = "Characters")
	TSubclassOf<ASmashCharacter> SmashCharacterClassP2;

	UPROPERTY(config, EditAnywhere, category = "Characters")
	TSubclassOf<ASmashCharacter> SmashCharacterClassP3;
};
