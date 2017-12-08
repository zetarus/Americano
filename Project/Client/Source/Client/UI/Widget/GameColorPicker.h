// // Copyright 2017-2018 Arcadia Company, Inc. All Rights Reserved.

#pragma once

// UnrealEngine
#include "CoreMinimal.h"
#include "UI/Widget/GameWidget.h"
// Client
#include "../../Common/Delegate.h"
#include "GameColorPicker.generated.h"

class UBorder;
class UImage;

/**
 * 
 */
UCLASS()
class CLIENT_API UGameColorPicker : public UGameWidget
{
	GENERATED_BODY()
	
	
private:	
	UImage*  ColorPickerIcon;
	UBorder* ColorWheel;

	/** To identify color of the widget. */
	FString WidgetName;

	FVector2D ColorPickerIconPosition;

	FVector2D ColorWheelSize;
	FVector2D ColorWheelHalfSize;
	bool      bColorWheelClicked;

	/** Hue */
	float H;
	/** Saturation */
	float S;
	/** Brightness */
	float V;

	/** Delegate used to get changing color. */
	FOnColorPickerSelectionChanged SelectionChanged;

public:
	UGameColorPicker(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	/** Delegate used to get changing color. */
	FOnColorPickerSelectionChanged& OnColorSelectionChanged() { return SelectionChanged; }

	void SetWidgetName(FString InName) { WidgetName = InName; }

	/** Set Color in RGB. */
	void SetColor(const FLinearColor& InRGB);

	void UpdateWidget(bool bSaveData=false);

	//Native SObjectWidget methods
protected:
	virtual FReply NativeOnMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	//~End Native SObjectWidget methods

private:	
	void CalculateHueAndSaturation();

	void GetColorWheelSize();

	FVector2D CalculateColorPickerIconPosition(const FGeometry& Geometry, const FPointerEvent& Input);
};
