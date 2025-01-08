#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "SmashCharacterSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, DefaultConfig, meta = (DisplayName = "Smash Character Settings"))
class SMASHUE_API USmashCharacterSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Input")
	TSoftObjectPtr<USmashCharachterInputData> InputData;

	UPROPERTY(Config, EditAnywhere, Category ="Inputs")
	TSoftObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(Config, EditAnywhere, Category="Input Settings")
	float InputMoveXThreshold;

	float GetInputMoveXThreshold() const { return InputMoveXThreshold; }
	
};
