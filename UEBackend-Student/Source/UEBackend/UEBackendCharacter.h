// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "UEBackendCharacter.generated.h"

USTRUCT()
struct FGameplayAbility
{
	GENERATED_BODY()

	UPROPERTY()
	FString Name;

	UPROPERTY()
	FString IconPath;

	UPROPERTY()
	bool IsEquipped;
};

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PlayerName;

	UPROPERTY()
	TArray<FGameplayAbility> Abilities;
};

USTRUCT()
struct FStatsStruct
{
	GENERATED_BODY()

	UPROPERTY()
	int32 PowerLevel;

	UPROPERTY()
	float Health;

	UPROPERTY()
	FString Rank;

	UPROPERTY()
	FString playername;
};


UCLASS(config=Game)
class AUEBackendCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

public:
	AUEBackendCharacter();

	UPROPERTY(EditAnywhere, Category = "Chat")
	TSubclassOf<class UChatWidget> WBP_ChatWidget;

	class UChatWidget* ChatWidgetInstance;
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

#pragma region Abilities

	void AddAbility(FString Name, FString IconPath);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FPlayerData PlayerData = {};

#pragma endregion


#pragma region Player Stats
public:
	UPROPERTY()
	FStatsStruct PlayerStats;

	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

#pragma endregion
};

