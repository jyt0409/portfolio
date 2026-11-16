#include "GrabComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"

UGrabComponent::UGrabComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

bool UGrabComponent::GetViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	const APawn* Pawn = Cast<APawn>(GetOwner());
	if (Pawn == nullptr || Pawn->GetController() == nullptr)
	{
		return false;
	}

	Pawn->GetController()->GetPlayerViewPoint(OutLocation, OutRotation);
	return true;
}

void UGrabComponent::ToggleGrab()
{
	
	if (GrabbedComponent)
	{
		ReleaseComponent();
		return;
	}

	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetViewPoint(ViewLocation, ViewRotation))
	{
		return;
	}


	const FVector Start = ViewLocation;
	const FVector End = Start + ViewRotation.Vector() * GrabRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner()); 

	FHitResult Hit;
	if (!GetWorld()->SweepSingleByChannel(Hit, Start, End,FQuat::Identity,ECC_Visibility,FCollisionShape::MakeSphere(20.0f),Params))
	{
		return; 
	}

	// Only grab objects that simulate physics
	UPrimitiveComponent* HitComponent = Hit.GetComponent();
	if (HitComponent == nullptr || !HitComponent->IsSimulatingPhysics())
	{
		return;
	}

	// Grab the object at its center
	GrabComponentAtLocationWithRotation(HitComponent, NAME_None,
		HitComponent->GetComponentLocation(), HitComponent->GetComponentRotation());
}

void UGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// move the target in front of the player while holding
	if (GrabbedComponent)
	{
		FVector ViewLocation;
		FRotator ViewRotation;
		if (GetViewPoint(ViewLocation, ViewRotation))
		{
			const FVector HoldLocation = ViewLocation + ViewRotation.Vector() * HoldDistance;
			const FRotator HoldRotation(0.0f, ViewRotation.Yaw, 0.0f); // face the same way as the player

			SetTargetLocationAndRotation(HoldLocation, HoldRotation);
		}
	}

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}