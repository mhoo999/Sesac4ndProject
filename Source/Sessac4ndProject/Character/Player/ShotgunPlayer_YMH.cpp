// zombie must die


#include "Character/Player/ShotgunPlayer_YMH.h"
#include "PlayerFireComp_YMH.h"
#include "PlayerController/PlayerController_YMH.h"
#include "UI/MainUI_YMH.h"

AShotgunPlayer_YMH::AShotgunPlayer_YMH()
{
	maxHelth = 10.0f;
	currentHealth = maxHelth;
	FireComp->attackSpeed = 5.0f;
	FireComp->Damage = 50.0f;
	FireComp->attackDistance = 1500;
	FireComp->weaponeGrade = 1;
	FireComp->MaxBulletCount = 5.0f;
	FireComp->bulletCount = 5.0f;
	FireComp->reloadBulletCount = 1.0f;
	FireComp->MaxRecoilValue = -1.0;
	FireComp->MinRecoilValue = -1.5;
	FireComp->crosshairRecoilValue = 3.0f;

}

void AShotgunPlayer_YMH::BeginPlay()
{
	Super::BeginPlay();
}

void AShotgunPlayer_YMH::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AShotgunPlayer_YMH::SetCrosshair()
{
	Super::SetCrosshair();

	/*auto pc = Cast<APlayerController_YMH>(Controller);
	if (pc)
	{
		pc->mainUI->ShowPointer();
		pc->mainUI->ShowCrosshair();
	}*/
}
