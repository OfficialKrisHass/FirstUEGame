#include "WeaponComponent.h"
#include "PlayerCharacter.h"

#include <Engine/GameEngine.h>

#include <Camera/CameraComponent.h>

#include <EnhancedInputComponent.h>
#include <InputActionValue.h>

UWeaponComponent::UWeaponComponent() {
	
	PrimaryComponentTick.bCanEverTick = true;

}

void UWeaponComponent::BeginPlay() {

	Super::BeginPlay();
	
}
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UWeaponComponent::Attach(APlayerCharacter* character) {

	m_character = character;

	APlayerController* controller = Cast<APlayerController>(m_character->GetController());
	if (controller == nullptr) return;

	UEnhancedInputComponent* inputComponent = Cast<UEnhancedInputComponent>(controller->InputComponent);
	if (inputComponent == nullptr) return;

	inputComponent->BindAction(fireAction, ETriggerEvent::Triggered, this, &UWeaponComponent::Fire);

}

void UWeaponComponent::Fire(const FInputActionValue& actionValue) {

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Weapon Fired"));

	if (!actionValue.Get<bool>()) return;

	FCollisionQueryParams params = FCollisionQueryParams(FName(TEXT("Fire params")), true, m_character);
	params.bReturnPhysicalMaterial = false;
	params.bDebugQuery = true;

	FHitResult hit = FHitResult(ForceInit);
	FVector start = m_character->GetCameraComponent()->GetComponentLocation();
	FVector end = start + (m_character->GetCameraComponent()->GetForwardVector() * 1500.0f);
	if (!GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_GameTraceChannel2, params)) return;

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, hit.GetActor()->GetName());
	hit.GetComponent()->AddImpulse(m_character->GetCameraComponent()->GetForwardVector() * 1000.0f * impactStrength);

}