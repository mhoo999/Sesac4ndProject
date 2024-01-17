// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrapBase.generated.h"

UCLASS()
class SESSAC4NDPROJECT_API ATrapBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrapBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* TileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BuildingCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* ReactionCollision;

	// TO DO :
	UPROPERTY()
	TArray<class AZombieBase_KJY*> EnemyArray;
	// class AZombieBase_KJY* Enemy;

	// TO DO :
	// UPROPERTY()
	// class APlayerBase* Player;

	int32 Cost = 350;
	int32 TrapAttackDamage = 0;
	float AttackCoolTime = 5;
	float CurrentTime = 0;
	int32 TrapInArea = 0;

	FTimerHandle Handle;

	UFUNCTION()
	virtual void OnEnemyBeginOverlapped(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnEnemyEndOverlapped(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
	
	virtual void UpgradeCost();
	virtual void UpgradeAbility();
	virtual void ReactTrap(TArray<AZombieBase_KJY*> EnemyBoxRef);
};
