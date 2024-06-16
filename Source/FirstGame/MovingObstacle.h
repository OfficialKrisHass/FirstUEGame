#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingObstacle.generated.h"

class USphereComponent;

UCLASS()
class FIRSTGAME_API AMovingObstacle : public AActor {

	GENERATED_BODY()
	
public:
	AMovingObstacle();

	virtual void Tick(float deltaTime) override;

private:
	UPROPERTY(EditAnywhere) float maxDistance = 50.0f;
	UPROPERTY(EditAnywhere) float offset = 0.0f;
	UPROPERTY(EditAnywhere) float movementSpeed = 1.0f;

	UPROPERTY(VisibleAnywhere) USphereComponent* collider;
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* mesh;

	FVector startLocation;
	FVector endLocation;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool fromSweep, const FHitResult& sweepResult);
	
};