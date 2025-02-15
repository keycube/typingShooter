// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "k3ShooterShop.h"
#include "k3Shooter/k3ShooterGameInstance.h"
#include "InputCoreTypes.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "k3ShooterCharacter.generated.h"

UCLASS()
class K3SHOOTER_API Ak3ShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	Ak3ShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlap(AActor* MyActor, AActor* OtherActor);

	UFUNCTION()
	void OnEndOverlap(AActor* MyActor, AActor* OtherActor);

	// Called When any key is pressed, responsible for handling A-Z key events to get the 
	void OnAnyKeyPress(FKey key);

	void ResetDefaultValues();

	//Camera
	UCameraComponent* Camera;

	//Useful variables for camera rotation into shop
	FRotator ShopRotationStart;
	FRotator ShopRotationEnd;
	float ShopRotationAlpha = 1.1f;

	//Target logic
	AActor* CurrentTarget;
	AActor* GetNearestEnemy();

	//Widget size
	float WidgetSizeList[10] = {0.5f, 0.466667f, 0.433333f, 0.38f, 0.32f, 0.29f, 0.255f, 0.23f, 0.21f, 0.2f};

public:	

	/**
	 * CHARACTER AND MAIN GAME
	 */

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Gun
	UStaticMeshComponent* GunModel;
	UWidgetComponent* GunWordWidget;

	void GetNewTargetWord();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString TargetWord = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Typed = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int CurrentWordLength = 3;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Health = 100; // Health is an int because it's easier to display and understand for the player. If the enemies ever do float damage, we'll have to floor it.

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Money = 0.0f; // On the contrary, Money is a float because the player is most likely familiar with cents. However, we'll need to display max 2 numbers after the period

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MoneyGain = 1.0f; // How much money you gain per enemy killed. Default 1.0

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DamagePerLetter = 1.0f; // Damage done to enemies can be a float because the enemies' HP is never displayed in text, only via a health bar, so no confusion here

	UFUNCTION(BlueprintCallable)
	FString GetCurrentWordProgress();

	// This function should be called by either this actor or other actors to hurt the player.
	// It takes care of killing the player, reducing the damage from some parameters (if added in the future), etc
	UFUNCTION(BlueprintCallable)
	void Hurt(float DamageTaken);

	// Fires X bullets at the enemies. This allows to hit multiple enemies with one word, provided they have low enough health.
	UFUNCTION(BlueprintCallable)
	void Fire();

	/**
	 * SHOP
	 */

	Ak3ShooterShop* Shop;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool IsInShop = false;

	UFUNCTION(BlueprintCallable)
	void ToggleShop();

	void ShopOnKeyPress(TCHAR n); // n = Name of the key. Ideally only call this on A-Z

	/**
	 * MISC
	 * Recoil, etc
	 */

	int RecoilAmount = 0;
	const float RecoilMovement = 0.50f;
	float RecoilMovementCurrent = 0.0f;
	float RecoilMovementMult = 1.0f;
};
