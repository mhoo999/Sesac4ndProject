// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Actor/ItemActor_KJY.h"
#include "HealthItem_KJY.generated.h"

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API AHealthItem_KJY : public AItemActor_KJY
{
	GENERATED_BODY()

	virtual void ReactItem() override;
};
