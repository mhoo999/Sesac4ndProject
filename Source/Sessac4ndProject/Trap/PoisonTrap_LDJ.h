// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Trap/TrapBase.h"
#include "PoisonTrap_LDJ.generated.h"

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API APoisonTrap_LDJ : public ATrapBase
{
	GENERATED_BODY()

	APoisonTrap_LDJ();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings")
	class UStaticMeshComponent* PoisonBottleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings")
	class UStaticMeshComponent* PoisonLiquid;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void UpgradeCost() override;
	virtual void UpgradeAbility() override;
	virtual void ReactTrap() override;

	FTimerHandle THandle;

	bool GoalArrived = false;

	
};
