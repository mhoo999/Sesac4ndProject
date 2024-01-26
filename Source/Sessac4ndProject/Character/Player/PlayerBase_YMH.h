// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase_YMH.h"
#include "InputActionValue.h"
#include "PlayerBase_YMH.generated.h"

class UPlayerUpgradeComp_YMH;
class UPointLightComponent;
class UMainUI_YMH;
class APlayerController_YMH;
class UPlayerBuildComp_LDJ;
class UPlayerFireComp_YMH;
class UPlayerMoveComp_YMH;
class UPlayerBaseComp_YMH;
struct FInputActionValue;
class UInputAction;
class AGameModeBase;
/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FInputDelegate, UInputComponent*);

UCLASS()
class SESSAC4NDPROJECT_API APlayerBase_YMH : public ACharacterBase_YMH
{
	GENERATED_BODY()

public:
	APlayerBase_YMH();

public:
	FInputDelegate OnSetupInputDelegate;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Components")
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Components")
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Components")
	USpringArmComponent* SelfCameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Components")
	USceneCaptureComponent2D* SelfCapture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|COmponents")
	UPointLightComponent* PointLightComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Inputs", meta = (AllowPrivateAccess))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly)
	UPlayerMoveComp_YMH* MoveComp;

	UPROPERTY(EditDefaultsOnly)
	UPlayerFireComp_YMH* FireComp;

	UPROPERTY(EditDefaultsOnly)
	UPlayerBuildComp_LDJ* BuildComp;

	UPROPERTY(EditDefaultsOnly)
	UPlayerUpgradeComp_YMH* UpgradeComp;
	
public:
	// ------------------- Init ----------------------
	UPROPERTY()
	APlayerController_YMH* playerController;

	UPROPERTY()
	UMainUI_YMH* mainUI;

	void VictoryProcess();
	virtual void SetCrosshair();
public:
	// ------------------- player HP ----------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stat")
	float maxHelth;
	
	UPROPERTY(BlueprintReadOnly, Category="Stat")
	float currentHealth = maxHelth;

	UFUNCTION(BlueprintCallable)
	virtual void BeShot(float damage);
	
	/*UFUNCTION(BlueprintCallable, Server, Reliable)
	virtual void ServerRPCBeShot(float damage);
	UFUNCTION(Client, Reliable)
	virtual void ClientRPCBeShot(float ch);*/
	
	void DieProcess();
	void RestorationHealth(float value);

	// ------------------- player mode --------------------
	bool bIsDead = false;				// 생사 여부
	bool bIsCombat = false;				// 전투중
	bool fireDispatcher = false;		// 공격 대기 상태 
	bool bIsBuildMode = false;			// 설치 모드
	UPROPERTY()
	bool bIsReloading = false;			// 장전중
	bool bIsDefeat = false;				// 패배 여부

	// ------------------- player inventory --------------------
	UPROPERTY()
	int32 wallet;
};

