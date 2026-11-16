#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GrabComponent.generated.h"

//pick up and carry objects
UCLASS(ClassGroup=(Custom),meta=(BlueprintSpawnableComponent))
class PORTFOLIO_API UGrabComponent : public UPhysicsHandleComponent
{
	GENERATED_BODY()

public:
	UGrabComponent();
	
	void ToggleGrab();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)override;

protected:
	//how far the player can grab
	UPROPERTY(EditAnywhere, Category = "Grab")
	float GrabRange = 300.0f;
	//how far in front of the camera the object is held
	UPROPERTY(EditAnywhere, Category = "Grab")
	float HoldDistance = 200.0f;

private:
	bool GetViewPoint(FVector& OutLocation, FRotator& OutRotation)const;
	
};
