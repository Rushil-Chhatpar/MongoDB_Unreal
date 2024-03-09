// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatWidget.generated.h"

/**
 * 
 */
UCLASS()
class UEBACKEND_API UChatWidget : public UUserWidget
{
	GENERATED_BODY()
	
	//UI HUD
public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ChatMessages = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UEditableTextBox* SendMessage = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* SendButton = nullptr;

	virtual bool Initialize() override;

	UFUNCTION()
	void SetIncomingMessages();
	/*FText SetIncomingMessages();*/


	//class AServerConnect* ServerCommunicator;
	
private:
	UFUNCTION()
	void SendButtonClicked();

	UFUNCTION()
	void OnMessageReceived(FString msg);
};
