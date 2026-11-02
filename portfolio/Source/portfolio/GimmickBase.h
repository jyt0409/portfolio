// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GimmickBase.generated.h"

UCLASS()
class PORTFOLIO_API AGimmickBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Called by a switch
	void RegisterSwitch(AActor* Switch);
	void NotifySwitchOn(AActor* Switch);
	virtual void Activate();

    private:
		TSet<AActor*> ConnectedSwitches;
		TSet<AActor*> OnSwitches;

		bool bActivated = false;
};
