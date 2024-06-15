#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "PlayerCharacter.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCharacter, Log, All);

class UCameraComponent;
class UInputAction;
struct FInputActionValue;

UCLASS()
class FIRSTGAME_API APlayerCharacter : public ACharacter {

	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere) UCameraComponent* camera;

	UPROPERTY(EditAnywhere) UInputAction* moveAction;
	UPROPERTY(EditAnywhere) UInputAction* lookAction;

	virtual void BeginPlay() override;

	void Move(const FInputActionValue& actionValue);
	void Look(const FInputActionValue& actionValue);
	
};