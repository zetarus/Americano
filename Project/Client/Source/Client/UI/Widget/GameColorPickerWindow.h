// // Copyright 2017-2018 Arcadia Company, Inc. All Rights Reserved.

#pragma once

// UnrealEngine Headers...
#include "CoreMinimal.h"
#include "UI/Widget/GameWidget.h"
// Client Headers...
#include "../../Common/Delegate.h"
#include "GameColorPickerHandler.h"
#include "GameColorPickerWindow.generated.h"

// UnrealEngine Class...
class USlider;
class UTextBlock;

// Client Class...
class FGameColorPickerHandler;
class UGameColorPicker;


/**
 * @brief	HSV Color Picker.
 */
UCLASS()
class CLIENT_API UGameColorPickerWindow : public UGameWidget
{
	GENERATED_BODY()
	
	
private:
	UTextBlock*			TbkColorName;
	UTextBlock*			TbkBrightnessName;
	UGameColorPicker*	UsrColorPicker;
	USlider*			SlrValueSlider;

	/** Delegate used to get changing the value element. */
	FOnValueSelectionChanged ValueSelectionChanged;

	/** Color Value in HSV. */
	FLinearColor		HSVColor;
	/** Widget Name */
	FString				WidgetName;
	/** ColorPicker Name */
	FString				ColorCaption;
	/** Value Slider Name */
	FString				BrightnessCaption;

	FEventHandlerMap	EventHandlerMap;

public:
	UGameColorPickerWindow(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void BeginDestroy() override;

	/** Delegate used to get changing value. */
	FOnValueSelectionChanged& OnValueSelectionChanged() { return ValueSelectionChanged; }

	void AddEventHandler(FGameColorPickerHandler* InTarget);

	void RemoveEventHandler(FGameColorPickerHandler* InTarget);

	void SetWidgetName(FString InName) { WidgetName = InName; }

	void SetColorWheelCaption(FString InCaption) { ColorCaption = InCaption; }

	void SetBrightnessCaption(FString InCaption) { BrightnessCaption = InCaption; }

	/** Set Color in RGB. */
	void SetColor(const FLinearColor& InRGB);

	void UpdateWidget(bool bSaveData=false);

	UFUNCTION()
	void OnColorValueChanged(float InValue);

	//Native SObjectWidget methods
protected:
	virtual FReply NativeOnMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent);
	virtual void NativeOnFocusLost(const FFocusEvent& InFocusEvent);
	virtual void NativeOnFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath, const FFocusEvent& InFocusEvent);
	//~End Native SObjectWidget methods
};
