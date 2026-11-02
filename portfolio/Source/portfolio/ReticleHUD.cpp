#include "ReticleHUD.h"
#include "Engine/Canvas.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"

void AReticleHUD::DrawHUD()
{
	Super::DrawHUD();

	if (!Canvas)
	{
		return;
	}
	if (PlayerOwner)
	{
		const bool bViewingPlayer = PlayerOwner->GetViewTarget() == PlayerOwner->GetPawn();
		const bool bCameraMoving = PlayerOwner->PlayerCameraManager && PlayerOwner->PlayerCameraManager->PendingViewTarget.Target != nullptr;

		if (!bViewingPlayer || bCameraMoving)
		{
			return;
		}
	}
	
	const float CX = Canvas->ClipX * 0.5f;
	const float CY = Canvas->ClipY * 0.5f;

	const int32 R = FMath::CeilToInt(Radius);
	for (int32 Y = -R; Y < R; ++Y)
	{
		const float DY = Y + 0.5f;
		const float HalfWidth = FMath::Sqrt(FMath::Max(0.0f, Radius * Radius - DY * DY));
		DrawRect(ReticleColor, CX - HalfWidth, CY + Y, HalfWidth * 2.0f, 1.0f);
	}
}