// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"
#include "FirstGameCharacter.h"
#include "FirstGameProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/AnimInstance.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"

UTP_WeaponComponent::UTP_WeaponComponent() {
	
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);

}

void UTP_WeaponComponent::Fire() {

	if (Character == nullptr || Character->GetController() == nullptr) return;

	if (ProjectileClass != nullptr) {

		UWorld* const World = GetWorld();
		if (World != nullptr) {

			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
	
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
			World->SpawnActor<AFirstGameProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

		}

	}
	
	if (FireSound != nullptr)
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	
	if (FireAnimation != nullptr) {

		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		
	}

}

bool UTP_WeaponComponent::AttachWeapon(AFirstGameCharacter* TargetCharacter) {

	Character = TargetCharacter;

	if (Character == nullptr || Character->GetInstanceComponents().FindItemByClass<UTP_WeaponComponent>()) return false;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));

	Character->AddInstanceComponent(this);

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController())) {

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			Subsystem->AddMappingContext(FireMappingContext, 1);

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Fire);
		
	}

	return true;

}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) {

	if (Character == nullptr) return;
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController())) {

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			Subsystem->RemoveMappingContext(FireMappingContext);
		
	}

}