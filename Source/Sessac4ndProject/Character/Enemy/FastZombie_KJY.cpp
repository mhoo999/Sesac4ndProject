// zombie must die


#include "Character/Enemy/FastZombie_KJY.h"

#include "GameFramework/CharacterMovementComponent.h"


AFastZombie_KJY::AFastZombie_KJY()
{
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void AFastZombie_KJY::BeginPlay()
{
	Super::BeginPlay();
}

void AFastZombie_KJY::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
