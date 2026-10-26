#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Switch.generated.h"

class AGimmickBase;
class UBoxComponent;
class UMaterialInterface;
class ACameraActor;

UCLASS()
class PORTFOLIO_API ASwitch : public AActor
{
	GENERATED_BODY()

public:
	ASwitch();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SwitchMesh;

	//Detect area
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;

	
	UPROPERTY(EditInstanceOnly)
	TArray<AGimmickBase*> Targets;

	UPROPERTY(EditAnyWhere)
	UMaterialInterface* PressedMaterial;

	UPROPERTY(EditInstanceOnly)
	ACameraActor* FocusCamera;

	UPROPERTY(EditAnyWhere)
	float FocusTime = 4.0f;

	UPROPERTY(EditAnyWhere)
	float BlendTime = 2.0f;

private:
	UFUNCTION()
	void OnPlayerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool bPressed = false;
	void EndFocus();

	UPROPERTY()
	APlayerController* FocusingController;
	FTimerHandle FocusTimerHandle;
};