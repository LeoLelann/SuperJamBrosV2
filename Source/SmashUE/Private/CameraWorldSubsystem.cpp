
#include "CameraWorldSubsystem.h"
//#include "CameraFollowTarget.h"
#include "EngineUtils.h"
//#include "MaterialHLSLTree.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

void UCameraWorldSubsystem::PostInitialize()
{
	Super::PostInitialize();
}

//void UCameraWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
//{
//	//Super::OnWorldBeginPlay(InWorld);
//	CameraMain = FindCameraByTag(TEXT("CameraMain"));
//
//	AActor* CameraBoundsActor = FindCameraBoundsActor();
//	if (CameraBoundsActor != nullptr)
//	{
//		InitCameraBounds(CameraBoundsActor);
//	}
//	InitCameraZoomParameters();
//}
//
//void UCameraWorldSubsystem::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//	TickUpdateCameraZoom(DeltaTime);
//	TickUpdateCameraPosition(DeltaTime);
//}
//
void UCameraWorldSubsystem::AddFollowTarget(UObject* FollowTarget)
{
	FollowTargets.Add(FollowTarget);
}

void UCameraWorldSubsystem::RemoveFollowTarget(UObject* FollowTarget)
{
	FollowTargets.Remove(FollowTarget);
}

//void UCameraWorldSubsystem::TickUpdateCameraZoom(float DeltaTime)
//{
//	if (CameraMain == nullptr) return;
//
//	float GreatestDistanceBetweenTargets = CalculateGreatestDistanceBetweenTargets();
//
//	//TODO: Slide 44 
//}
//
//void UCameraWorldSubsystem::TickUpdateCameraPosition(float DeltaTime)
//{
//	FVector TargetPosition = CalculateAveragePositionBetweenTargets();
//	FVector CurrentPosition = CameraMain->GetComponentLocation();
//	FVector NewPosition = FMath::VInterpTo(CurrentPosition, TargetPosition, DeltaTime, 3.0f);
//	NewPosition.Y = 1500.f;
//	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan,NewPosition.ToString());
//
//	
//	
//	CameraMain->SetWorldLocation(NewPosition);
//}
//
//FVector UCameraWorldSubsystem::CalculateAveragePositionBetweenTargets() const
//{
//	if (FollowTargets.Num() == 0)
//	{
//		return FVector::ZeroVector;
//	}
//
//	FVector AveragePosition = FVector::ZeroVector;
//
//	for (const AActor* Target : FollowTargets)
//	{
//		if (Target)
//		{
//			AveragePosition += Target->GetActorLocation();
//		}
//	}
//
//	return AveragePosition / FollowTargets.Num();
//}
//
//FVector UCameraWorldSubsystem::CalculateAveragePositionBetweenTargets()
//{
//	if (FollowTargets.Num() == 0)
//	{
//		return FVector::ZeroVector;
//	}
//
//	FVector AveragePosition = FVector::ZeroVector;
//
//	for ( const UObject* Target : FollowTargets)
//	{
//		if (Target)
//		{
//			AveragePosition += Target->GetActorLocation();
//		}
//	}
//
//	if (IsFollowable = true)
//
//	return AveragePosition / FollowTargets.Num();
//}
//
//float UCameraWorldSubsystem::CalculateGreatestDistanceBetweenTargets()
//{
//	float GreatestDistance = 0.f;
//
//	//TODO: Slide 45
//	
//	return GreatestDistance;
//}

UCameraComponent* UCameraWorldSubsystem::FindCameraByTag(const FName& Tag) const
{
	for (TActorIterator<AActor> It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (Actor->ActorHasTag(Tag))
		{
			UCameraComponent* CameraComponent = Actor->FindComponentByClass<UCameraComponent>();
			if (CameraComponent)
			{
				return CameraComponent;
			}
		}
	}
	return nullptr;
}

//void UCameraWorldSubsystem::InitCameraZoomParameters()
//{
//	//TODO: slide 42 
//}

//AActor* UCameraWorldSubsystem::FindCameraBoundsActor()
//{
//	//TODO: Find First Actor with tag "CameraBounds" slide29 
//	return nullptr;
//}

//void UCameraWorldSubsystem::InitCameraBounds(AActor* CameraBoundsActor)
//{
//	FVector BoundsCenter;
//	FVector BoundsExtents;
//	CameraBoundsActor->GetActorBounds(false, BoundsCenter, BoundsExtents);
//
//	//TODO: Fill CameraBounds and CameraYProjectionCenter according to bounds slide 30 
//}

//void UCameraWorldSubsystem::ClampPositionIntoCameraBounds(FVector2d& Position)
//{
//	FVector2d ViewportBoundsMin, ViewportBoundsMax;
//	GetViewportBounds(ViewportBoundsMin, ViewportBoundsMax);
//
//	FVector WorldBoundsMin = CalculateWorldPositionFromViewportPosition(ViewportBoundsMin);
//	FVector WorldBoundsMax = CalculateWorldPositionFromViewportPosition(ViewportBoundsMax);
//
//	//TODO: Clamp Position according to WorldBounds 
//}

void UCameraWorldSubsystem::GetViewportBounds(FVector2d& OutViewportBoundsMin, FVector2d& OutViewportBoundsMax)
{
	//Find Viewport
	UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
	if (ViewportClient == nullptr) return;

	FViewport* Viewport = ViewportClient->Viewport;
	if (Viewport == nullptr) return;

	//Calculate Viewport Rect according to Camera Aspect Ratio and Viewport ViexRect
	FIntRect ViewRect(
		Viewport->GetInitialPositionXY(),
		Viewport->GetInitialPositionXY() + Viewport->GetSizeXY()
		);
	FIntRect ViewportRect = Viewport->CalculateViewExtents(CameraMain->AspectRatio, ViewRect);

	//Fill Output parameters with ViewportRect
	OutViewportBoundsMin.X = ViewportRect.Min.X;
	OutViewportBoundsMin.Y = ViewportRect.Min.Y;

	OutViewportBoundsMax.X = ViewportRect.Max.X;
	OutViewportBoundsMax.Y = ViewportRect.Max.Y;
}

FVector UCameraWorldSubsystem::CalculateWorldPositionFromViewportPosition(const FVector2D& ViewportPosition)
{
	if (CameraMain == nullptr) return FVector::Zero();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController == nullptr) return FVector::Zero();

	float YDistanceToCenter = CameraMain->GetOwner()->GetActorLocation().Y - CameraBoundsYProjectionCenter;

	FVector CameraWorldProjectDir;
	FVector WorldPosition;

	UGameplayStatics::DeprojectScreenToWorld(
		PlayerController,
		ViewportPosition,
		WorldPosition,
		CameraWorldProjectDir
		);

	WorldPosition += CameraWorldProjectDir * YDistanceToCenter;
	
	return WorldPosition;
}
