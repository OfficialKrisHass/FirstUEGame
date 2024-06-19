#include "BreakableActor.h"

ABreakableActor::ABreakableActor() {

	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetMobility(EComponentMobility::Movable);
	mesh->SetSimulatePhysics(true);
	mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);

	RootComponent = mesh;

}

void ABreakableActor::BeginPlay() {

	Super::BeginPlay();

}

void ABreakableActor::Tick(float deltaTime) {

	Super::Tick(deltaTime);

}

void ABreakableActor::Hit(float damage) {

	if (m_health - damage <= 0.0f) {

		Break();
		return;

	}

	m_health -= damage;

}

void ABreakableActor::Break() {

	m_health = 0.0f;
	Super::Destroy();

}