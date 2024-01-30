// zombie must die


#include "Actor/ItemActor_KJY.h"
#include "Character/Player/PlayerBase_YMH.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AItemActor_KJY::AItemActor_KJY()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	RootComponent = collisionComp;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AItemActor_KJY::BeginPlay()
{
	Super::BeginPlay();

	collisionComp->OnComponentBeginOverlap.AddDynamic(this, &AItemActor_KJY::OnBeginItemOverlap);

}

// Called every frame
void AItemActor_KJY::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemActor_KJY::OnBeginItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority())
	{
		Player = Cast<APlayerBase_YMH>(OtherActor);
	
		if (Player == OtherActor)
		{
			ReactItem();
			Destroy();
		}
	}
}

void AItemActor_KJY::ReactItem()
{
}