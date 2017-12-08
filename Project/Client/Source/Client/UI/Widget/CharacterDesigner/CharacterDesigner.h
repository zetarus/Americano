// // Copyright 2017-2018 Arcadia Company, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/GameWidget.h"
#include "../GameColorPickerHandler.h"
#include "CharacterDesigner.generated.h"

class UGameColorPicker;
class UGameColorPickerWindow;

/**
 * 
 */
UCLASS()
class CLIENT_API UCharacterDesigner
	: public UGameWidget
	, public FGameColorPickerHandler
{
	GENERATED_BODY()
	
public:
	
private:
	UGameColorPickerWindow* UsrColorPickerSkin;
	UGameColorPickerWindow* UsrColorPickerIris;
	UGameColorPickerWindow* UsrColorPickerHair;

	FLinearColor SkinColor;
	FLinearColor HairColor;
	FLinearColor IrisColor;

	FLinearColor CurrentSkinColor;;
	FLinearColor CurrentHairColor;;
	FLinearColor CurrentIrisColor;;

public:
	UCharacterDesigner(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "CharacterDesigner")
	void InitSkinColor(const FLinearColor& InRGBColor);

	UFUNCTION(BlueprintCallable, Category = "CharacterDesigner")
	void InitHairColor(const FLinearColor& InRGBColor);

	UFUNCTION(BlueprintCallable, Category = "CharacterDesigner")
	void InitIrisColor(const FLinearColor& InRGBColor);

	/** Delegate used to get changing color. */
	UFUNCTION(BlueprintNativeEvent, Category = "CharacterDesigner")
	void OnCharacterColorChanged(const FString& InColorName, const FLinearColor& InColor);

public:
	virtual void BeginDestroy() override;

protected:
	virtual void NativeConstruct() override;

	virtual void HandleColorPickerColorChanged(FString& InColorName, FLinearColor& InColor) override;

	virtual void HandleColorPickerBrightnessChanged(FString& InColorName, float InColorValue) override;
};
