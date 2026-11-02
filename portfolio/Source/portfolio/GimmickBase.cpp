#include "GimmickBase.h"

void AGimmickBase::RegisterSwitch(AActor* Switch)
{
	if (Switch)
	{
		ConnectedSwitches.Add(Switch);
	}
}

void AGimmickBase::NotifySwitchOn(AActor* Switch)
{
	if (bActivated || !ConnectedSwitches.Contains(Switch))
	{
		return;
	}
	OnSwitches.Add(Switch);
	//Activate when every switch is ON
	if (OnSwitches.Num() >= ConnectedSwitches.Num())
	{
		bActivated = true;
		Activate();
	}
}
void AGimmickBase::Activate()
{

}
