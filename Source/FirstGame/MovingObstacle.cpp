#include "MovingObstacle.h"
#include "PlayerCharacter.h"

#include "Components/SphereComponent.h"

AMovingObstacle::AMovingObstacle() {

	PrimaryActorTick.bCanEverTick = true;

	collider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	collider->OnComponentBeginOverlap.AddDynamic(this, &AMovingObstacle::OnBeginOverlap);
	RootComponent = collider;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(collider);

}

void AMovingObstacle::BeginPlay() {

	Super::BeginPlay();

	startLocation = GetActorLocation();
	endLocation = startLocation;
	endLocation.X += maxDistance;

}

void AMovingObstacle::Tick(float deltaTime) {

	Super::Tick(deltaTime);

	float alpha = (FMath::Sin((GetGameTimeSinceCreation() + deltaTime) * movementSpeed + offset * PI) + 1) / 2;
	SetActorLocation(FMath::Lerp(startLocation, endLocation, alpha));

}
void AMovingObstacle::OnBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool fromSweep, const FHitResult& sweepResult) {

	APlayerCharacter* player = Cast<APlayerCharacter>(otherActor);
	if (player == nullptr) return;

	player->Respawn();

}