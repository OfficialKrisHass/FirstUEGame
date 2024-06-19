#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BreakableActor.generated.h"

UCLASS()
class FIRSTGAME_API ABreakableActor : public AActor {

	GENERATED_BODY()
	
public:
	ABreakableActor();

	virtual void Tick(float deltaTime) override;

	void Hit(float damage);

private:
	UPROPERTY(EditAnywhere) float m_maxHealth = 100;
	UPROPERTY(EditAnywhere) float m_health = m_maxHealth;

	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* mesh;

	virtual void BeginPlay() override;

	void Break();
	
};