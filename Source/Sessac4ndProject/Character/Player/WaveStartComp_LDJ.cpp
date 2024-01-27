// zombie must die


#include "Character/Player/WaveStartComp_LDJ.h"

#include "EnhancedInputComponent.h"
#include "PlayerBase_YMH.h"
#include "Animation/PlayerAnimInstance_YMH.h"
#include "Character/Enemy/ZombieBase_KJY.h"
#include "Character/Enemy/ZombieManagerBase_KJY.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerController/PlayerController_YMH.h"
#include "UI/MainUI_YMH.h"
#include "UI/WaveInformationUI_LDJ.h"

UWaveStartComp_LDJ::UWaveStartComp_LDJ()
{
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_WaveStartRef(
		TEXT("/Game/LDJ/Input/IA_WaveStart.IA_WaveStart"));
	if (IA_WaveStartRef.Succeeded()) IA_WaveStart = IA_WaveStartRef.Object;
}

void UWaveStartComp_LDJ::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AZombieManagerBase_KJY::StaticClass(), ZombieManagerArray);
	auto PC = GetWorld()->GetFirstPlayerController();
	MyPlayerController = Cast<APlayerController_YMH>(PC);
}

void UWaveStartComp_LDJ::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWaveStartComp_LDJ::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_WaveStart, ETriggerEvent::Started, this, &UWaveStartComp_LDJ::WaveStart);
	}
}

void UWaveStartComp_LDJ::WaveStart(const FInputActionValue& value) //임시로 쓰는 웨이브 시작 트래커
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("%d"), GetNetMode()));
	if (bWaveClear && GetWorld()->GetFirstPlayerController()->HasAuthority())
	{
		ServerRPC_WaveStart();
	}
}

void UWaveStartComp_LDJ::ServerRPC_WaveStart_Implementation()
{
	for (const auto e : ZombieManagerArray)
	{
		Temp = Cast<AZombieManagerBase_KJY>(e);
		Temp->CurrentWave++;
		// GetWorld()->GetTimerManager().UnPauseTimer(Temp->SpawnTimerHandle);
	}
	MultiRPC_WaveStart(Temp->CurrentWave);
}

void UWaveStartComp_LDJ::MultiRPC_WaveStart_Implementation(int32 CurrentWave)
{
	GetWorld()->GetTimerManager().SetTimer(TextHandle, FTimerDelegate::CreateLambda([&]
	{
		MyPlayerController->mainUI->WBP_WaveInfor->SetWaveText(FText::GetEmpty());
	}), 2, false);
	bWaveClear = false;

	GetWorld()->GetTimerManager().SetTimer(ZombieDieHandle, FTimerDelegate::CreateLambda([&]
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AZombieBase_KJY::StaticClass(), LivingZombieArray);
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green,
		                                 FString::Printf(TEXT("Enemy : %d"), LivingZombieArray.Num()));
		if (LivingZombieArray.Num() == 0 && ZombieSpawnManager->CurrentWave < 3)
		{
			MyPlayerController->mainUI->WBP_WaveInfor->SetWaveText(
				FText::FromString(FString::Printf(TEXT("GET READY FOR THE NEXT WAVE\r\n PRESS 'G' KEY"))));
			GetWorld()->GetTimerManager().ClearTimer(ZombieDieHandle);
			bWaveClear = true;
		}
		else if (LivingZombieArray.Num() == 0 && ZombieSpawnManager->CurrentWave > 2)
		{
			GetWorld()->GetTimerManager().ClearTimer(ZombieDieHandle);
			MyPlayerController->mainUI->WBP_WaveInfor->SetWaveText(FText::FromString(FString::Printf(TEXT("YOU WIN"))));
			auto AnimTemp = Cast<UPlayerAnimInstance_YMH>(
				GetWorld()->GetFirstPlayerController()->GetCharacter()->GetMesh()->GetAnimInstance());
			AnimTemp->PlayVictoryMontage();
			player->GetCharacterMovement()->bUseControllerDesiredRotation = false;
			
			GetWorld()->GetTimerManager().SetTimer(WinHandle, FTimerDelegate::CreateLambda([&]
			{
				UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(),
				                               EQuitPreference::Quit, false);
			}), 10, false);
		}
	}), 1, true, 5);
	ZombieSpawnManager = Cast<AZombieManagerBase_KJY>(ZombieManagerArray[0]);
	MyPlayerController->mainUI->WBP_WaveInfor->SetWaveText(FText::FromString(FString::Printf(TEXT("Wave%d Start"), CurrentWave)));
}
