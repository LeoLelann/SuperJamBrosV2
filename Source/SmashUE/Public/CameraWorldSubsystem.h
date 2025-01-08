// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Subsystems/WorldSubsystem.h"
//#include "CameraFollowTarget.h"
#include "CameraWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SMASHUE_API UCameraWorldSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void PostInitialize() override;

	//virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	//virtual void Tick(float DeltaTime) override;

	virtual TStatId GetStatId() const override { return TStatId(); };

protected:
	UCameraComponent* FindCameraByTag(const FName& Tag) const;

#pragma region MainCamera

protected:
	UPROPERTY()
    TObjectPtr<UCameraComponent> CameraMain;

	//void TickUpdateCameraZoom(float DeltaTime);

	//void TickUpdateCameraPosition(float DeltaTime);

#pragma endregion
#pragma region FollowTargets

public:
	void AddFollowTarget(UObject* FollowTarget);
       
	void RemoveFollowTarget(UObject* FollowTarget);

protected:
	UPROPERTY()
    TArray<UObject*> FollowTargets;

	//FVector CalculateAveragePositionBetweenTargets();

	//float CalculateGreatestDistanceBetweenTargets();

#pragma endregion
#pragma region Zoom

protected:
	UPROPERTY()
	float CameraZoomYMin = 0.f;

	UPROPERTY()
	float CameraZoomYMax = 0.f;

	UPROPERTY()
	float CameraZoomDistanceBetweenTargetsMin = 300.f;

	UPROPERTY()
	float CameraZoomDistanceBetweenTargetsMax = 1500.f;

	//UPROPERTY()
	//void InitCameraZoomParameters();

#pragma endregion
#pragma region Bounds

protected:
	UPROPERTY()
	FVector CameraBoundsMin;

	UPROPERTY()
	FVector CameraBoundsMax;

	UPROPERTY()
	float CameraBoundsYProjectionCenter;

	//AActor* FindCameraBoundsActor();

	//void InitCameraBounds(AActor* CameraBoundsActor);

	//void ClampPositionIntoCameraBounds(FVector2d& Position);

	void GetViewportBounds(FVector2d& OutViewportBoundsMin, FVector2d& OutViewportBoundsMax);

	FVector CalculateWorldPositionFromViewportPosition(const FVector2D& ViewportPosition);

	#pragma endregion
};
