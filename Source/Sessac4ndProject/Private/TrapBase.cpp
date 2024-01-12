// zombie must die


#include "TrapBase.h"

#include "Components/BoxComponent.h"

// Sets default values
ATrapBase::ATrapBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BuildingCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Building Component"));
	SetRootComponent(BuildingCollision);
	BuildingCollision->SetBoxExtent(FVector(100,100,5));
	
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile Mesh Component"));
	TileMesh->SetupAttachment(RootComponent);
	TileMesh->SetRelativeScale3D(FVector(1.25,1.25,1));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> TileMeshRef(TEXT("/Game/SimpleApocalypse/Meshes/Environment/SM_Env_ManholeClosed_01.SM_Env_ManholeClosed_01"));
    if (TileMeshRef.Object)
    {
		TileMesh->SetStaticMesh(TileMeshRef.Object);
    }
	ReactionCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Enemy Sensing Component"));
	ReactionCollision->SetupAttachment(RootComponent);
	ReactionCollision->SetBoxExtent(FVector(100));
}

// Called when the game starts or when spawned
void ATrapBase::BeginPlay()
{
	Super::BeginPlay();
	ReactionCollision->OnComponentBeginOverlap.AddDynamic(this, &ATrapBase::OnEnemyOverlapped);
	ReactionCollision->OnComponentEndOverlap.AddDynamic(this, &ATrapBase::OnEnemyEndOverlapped);
}

// Called every frame
void ATrapBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATrapBase::OnEnemyOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TO DO : 플레이어한테 반응하는거 에너미로 바꾸기
	auto Temp = Cast<AActor>(OtherActor);
	if (Temp)
	{
		TrapInArea++;
	}

	if (TrapInArea == 1)
	{
		ReactTrap();
	}
	
	if (TrapInArea > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([this]()->void
		{
			ReactTrap();
			UE_LOG(LogTemp,Warning, TEXT("Still In Trap"));
		}), AttackCoolTime, true);	
	}
}

void ATrapBase::OnEnemyEndOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto Temp = Cast<AActor>(OtherActor);
	if (Temp)
	{
		TrapInArea--;
	}

	if (TrapInArea == 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(Handle);	
	}
}

void ATrapBase::UpgradeCost()
{
	this->Cost -= 50;
}

void ATrapBase::UpgradeAbility()
{
}

void ATrapBase::ReactTrap()
{
	UE_LOG(LogTemp,Warning, TEXT("Parent Trap"));
}

