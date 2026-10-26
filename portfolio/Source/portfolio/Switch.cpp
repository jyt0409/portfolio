#include "Switch.h"
#include "GimmickBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Pawn.h"

ASwitch::ASwitch()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	SwitchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwitchMesh"));
	SwitchMesh->SetupAttachment(Root);
	SwitchMesh->SetMobility(EComponentMobolity::Movable);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(Root);
	TriggerBox->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
}

void ASwitch::BeginPlay()
{
	Super::BeginPlay();

	// When something enters the box, call OnPlayerEnter
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASwitch::OnPlayerEnter);
}

void ASwitch::OnPlayerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bPressed)
	{
		return;
	}

	// Only react to the player
	APawn* Pawn = Cast<APawn>(OtherActor);
	if (Pawn == nullptr || !Pawn->IsPlayerControlled())
	{
		return;
	}

	bPressed = true;
	// Change the look of the switch so the player knows it was pressed
	SwitchMesh->AddLocalOffset(FVector(0.0f, 0.0f, -PressDepth));
	if (PressedMaterial)
	{
		SwitchMesh->SetMaterial(0, PressedMaterial);
	}

	// Activate every target gimmick
	for (AGimmickBase* Target : Targets)
	{
		if (Target)
		{
			Target->Activate();
		}
	}
}