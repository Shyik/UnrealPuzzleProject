#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_X_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	UPROPERTY(EditAnywhere)
		float TraceLength = 100.0f;

	UPhysicsHandleComponent* MyPhysicsHandle = nullptr;

	UInputComponent* MyInputComponent = nullptr;

	void Grab();
	void GrabRelease();

	void SetupInputComponent();
	void FindPhysiscsHandle();

	FHitResult GetFirstPhysicsBodyInReach();
	FVector GetLineTraceEnd();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
