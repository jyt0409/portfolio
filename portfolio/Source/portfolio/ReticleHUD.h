#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ReticleHUD.generated.h"

UCLASS()
class PORTFOLIO_API AReticleHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Reticle")
	float ReticleSize = 6.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Reticle")
	FLinearColor ReticleColor = FLinearColor::White;
};