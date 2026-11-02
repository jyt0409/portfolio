#include "Switch.h"
#include "GimmickBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraActor.h"
#include "TimerManager.h"


ASwitch::ASwitch()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	SwitchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwitchMesh"));
	SwitchMesh->SetupAttachment(Root);
	

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(Root);
	TriggerBox->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
}

void ASwitch::BeginPlay()
{
	Super::BeginPlay();

	// When something enters the box, call OnPlayerEnter
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASwitch::OnPlayerEnter);
	//Tell each target gimmick that this switch is connected to itB
	for (AGimmickBase* Target:Targets)
	{
		if (Target)
		{
			Target->RegisterSwitch(this);
		}
	}
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
	if (PressedMaterial)
	{
		SwitchMesh->SetMaterial(0, PressedMaterial);
	}

	// Activate every target gimmickb
	for (AGimmickBase* Target : Targets)
	{
		if (Target)
		{
			Target->NotifySwitchOn(this);
		}
	}
	if (FocusCamera)
	{
		APlayerController* PC = Cast<APlayerController>(Pawn->GetController());
		if (PC)
		{
			FocusingController = PC;
			Pawn->DisableInput(PC);
			PC->SetViewTargetWithBlend(FocusCamera, BlendTime);
			GetWorldTimerManager().SetTimer(FocusTimerHandle, this, &ASwitch::EndFocus, FocusTime, false);
		}
	}
}
	void ASwitch::EndFocus()
	{
		if (FocusingController)
		{
			APawn* Pawn = FocusingController->GetPawn();
			if (Pawn)
			{
				FocusingController->SetViewTargetWithBlend(Pawn, BlendTime);
				Pawn->EnableInput(FocusingController);
			}
		}
		FocusingController = nullptr;
	}
