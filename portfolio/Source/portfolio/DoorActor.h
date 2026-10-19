#pragma once

#include "CoreMinimal.h"
#include "GimmickBase.h"
#include "DoorActor.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API ADoorActor : public AGimmickBase
{
	GENERATED_BODY()
	

public:
	ADoorActor();

	virtual void Tick(float DeltaTime) override;
	virtual void Activate() override;

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorMesh;

    //Height
	UPROPERTY(EditAnywhere)
	float OpenHeight = 300.0f;

	//Move Speed
	UPROPERTY(EditAnywhere)
	float OpenSpeed = 100.0f;

private :
	bool bOpened = false;
	float MovedHeight = 0.0f;
};
