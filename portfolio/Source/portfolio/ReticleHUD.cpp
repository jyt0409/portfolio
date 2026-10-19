#include "ReticleHUD.h"
#include "Engine/Canvas.h"

void AReticleHUD::DrawHUD()
{
	Super::DrawHUD();

	if (!Canvas)
	{
		return;
	}

	const float CenterX = Canvas->ClipX * 0.5f;
	const float CenterY = Canvas->ClipY * 0.5f;
	const float Half = ReticleSize * 0.5f;

	DrawRect(ReticleColor, CenterX - Half, CenterY - Half, ReticleSize, ReticleSize);
}