// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SessionSlotWidget_LDJ.generated.h"

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API USessionSlotWidget_LDJ : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UTextBlock* Txt_SessionNumber;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UTextBlock* Txt_RoomName;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UTextBlock* Txt_HostName;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UTextBlock* Txt_PlayerCount;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UTextBlock* Txt_PingSpeed;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UButton* Btn_Join;

	int32 SessionNumber;
	void Set(const struct FSessionInfo& SessionInfo);

	// //세션 들어가기
	// virtual void NativeConstruct() override;
	//
	// UFUNCTION()
	// void JoinSession();
};
