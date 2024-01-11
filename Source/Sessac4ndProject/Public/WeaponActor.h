// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

UCLASS()
class SESSAC4NDPROJECT_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
