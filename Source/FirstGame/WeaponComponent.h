#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WeaponComponent.generated.h"

class APlayerCharacter;

class UInputAction;
struct FInputActionValue;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIRSTGAME_API UWeaponComponent : public USkeletalMeshComponent {

	GENERATED_BODY()

public:
	UWeaponComponent();

	void Attach(APlayerCharacter* character);

	virtual void TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction) override;

private:
	UPROPERTY(EditAnywhere) float impactStrength = 10.0f;

	UPROPERTY(EditAnywhere) UInputAction* fireAction;

	APlayerCharacter* m_character;

	virtual void BeginPlay() override;

	void Fire(const FInputActionValue& actionValue);
	
};