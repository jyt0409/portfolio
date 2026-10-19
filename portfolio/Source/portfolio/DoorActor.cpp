#include "DoorActor.h"
#include "Components/StaticMeshComponent.h"

ADoorActor::ADoorActor()
{
	// Allow Tick to be called every frame
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetMobility(EComponentMobility::Movable);
	RootComponent = DoorMesh;
}

void ADoorActor::Activate()
{
	// Just start opening. Tick does the moving.
	bOpened = true;
}

void ADoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Not opened yet, or already fully open
	if (!bOpened || MovedHeight >= OpenHeight)
	{
		return;
	}

	// Distance to move this frame
	float Step = OpenSpeed * DeltaTime;

	// Do not go past the top
	if (MovedHeight + Step > OpenHeight)
	{
		Step = OpenHeight - MovedHeight;
	}

	MovedHeight += Step;
	AddActorWorldOffset(FVector(0.0f, 0.0f, Step));
}