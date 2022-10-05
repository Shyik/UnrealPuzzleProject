#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysiscsHandle();
	SetupInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(MyPhysicsHandle->GrabbedComponent)
	{
		MyPhysicsHandle->SetTargetLocation(GetLineTraceEnd());
	}
}


void UGrabber::Grab()
{
	UE_LOG(LogTemp, Error, TEXT("Grab!"));

	FHitResult Hit;
	Hit = GetFirstPhysicsBodyInReach();

	if(Hit.GetComponent()&& MyPhysicsHandle)
	{
		MyPhysicsHandle->GrabComponentAtLocation(Hit.GetComponent(), NAME_None, GetLineTraceEnd());
	}
}
void UGrabber::GrabRelease()
{
	UE_LOG(LogTemp, Error, TEXT("Grab Released!"));
	if (MyPhysicsHandle->GrabbedComponent)
	{
		MyPhysicsHandle->ReleaseComponent();
	}
}

void UGrabber::FindPhysiscsHandle()
{
	//UE_LOG(LogTemp, Warning, TEXT("Grabber funkt!"));

	MyPhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	

	if (MyPhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("PhysicsHandle Klappt!"));
	} 
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("PhysicsHandle nicht Gefunden"));
	}
}

void UGrabber::SetupInputComponent()
{
	MyInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (MyInputComponent)
	{
		MyInputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		MyInputComponent->BindAction("Grab", IE_Released, this, &UGrabber::GrabRelease);
		UE_LOG(LogTemp, Error, TEXT("MyInputComponent binding ok"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MyInputComponent nicht Gefunden")); 
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	//UE_LOG(LogTemp, Warning, TEXT("Location: %s | Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());
	
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * TraceLength;
	
	//Kann man sich merken, ist Praktisch!!!
	//DrawDebugLine(GetWorld(),PlayerViewPointLocation, LineTraceEnd, FColor(0,255,0), false, 0.f,0, 5.f);
	
	FHitResult Hit;
	FCollisionQueryParams Traceparams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(OUT Hit,PlayerViewPointLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), Traceparams);

	AActor* ActorHitted = Hit.GetActor();

	if (ActorHitted) 
	{
		UE_LOG(LogTemp, Error, TEXT("Getroffenes Object: %s"), *ActorHitted->GetName());
	}
	return Hit;
}

FVector UGrabber::GetLineTraceEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	//UE_LOG(LogTemp, Warning, TEXT("Location: %s | Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());
	
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * TraceLength;

	return LineTraceEnd;
}

