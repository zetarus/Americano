// // Copyright 2017-2018 Arcadia Company, Inc. All Rights Reserved.

#include "GameColorPickerWindow.h"
#include "Client.h"

UGameColorPickerWindow::UGameColorPickerWindow(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, TbkColorName(nullptr)
	, UsrColorPicker(nullptr)
	, SlrValueSlider(nullptr)
{
}

void UGameColorPickerWindow::NativeConstruct()
{
	Super::NativeConstruct();

	TbkColorName		= Cast< UTextBlock >(WidgetTree->FindWidget(TEXT("ColorName")));
	TbkBrightnessName   = Cast< UTextBlock >(WidgetTree->FindWidget(TEXT("Brightness")));
	UsrColorPicker		= Cast< UGameColorPicker >(WidgetTree->FindWidget(TEXT("ColorPicker")));
	SlrValueSlider		= Cast< USlider >(WidgetTree->FindWidget(TEXT("ValueSlider")));
	
	SlrValueSlider->OnValueChanged.AddDynamic(this, &UGameColorPickerWindow::OnColorValueChanged);

	UpdateWidget();
}

void UGameColorPickerWindow::BeginDestroy()
{
	if ( SlrValueSlider )
	{
		SlrValueSlider->OnValueChanged.RemoveDynamic(this, &UGameColorPickerWindow::OnColorValueChanged);
		SlrValueSlider = nullptr;
	}
	Super::BeginDestroy();
}

void UGameColorPickerWindow::AddEventHandler(FGameColorPickerHandler* InTarget)
{
	if ( UsrColorPicker )
	{
		FDelegateHandleArray& EventHandles = EventHandlerMap.Add(InTarget);
		FDelegateHandle DelegateHandleColorChanged = UsrColorPicker->OnColorSelectionChanged().AddRaw(InTarget, &FGameColorPickerHandler::HandleColorPickerColorChanged);
		EventHandles.Add(DelegateHandleColorChanged);

		FDelegateHandle DelegateHandleBrightnessChanged = OnValueSelectionChanged().AddRaw(InTarget, &FGameColorPickerHandler::HandleColorPickerBrightnessChanged);
		EventHandles.Add(DelegateHandleBrightnessChanged);
	}
}

void UGameColorPickerWindow::RemoveEventHandler(FGameColorPickerHandler* InTarget)
{
	if ( UsrColorPicker )
	{
		FDelegateHandleArray* DelegateHandleArrayPtr = EventHandlerMap.Find(InTarget);
		if ( DelegateHandleArrayPtr )
		{
			UsrColorPicker->OnColorSelectionChanged().Remove((*DelegateHandleArrayPtr)[0]);
			OnValueSelectionChanged().Remove((*DelegateHandleArrayPtr)[1]);
		}
	}
}

void UGameColorPickerWindow::SetColor(const FLinearColor& InRGB)
{
	HSVColor = InRGB.LinearRGBToHSV();
}

void UGameColorPickerWindow::UpdateWidget(bool bSaveData/*=false*/)
{
	if (bSaveData)
	{
		return;
	}
	TbkColorName->SetText(FText::FromString(ColorCaption));
	TbkBrightnessName->SetText(FText::FromString(BrightnessCaption));
	UsrColorPicker->SetWidgetName(WidgetName);
}

void UGameColorPickerWindow::OnColorValueChanged(float InValue)
{
	HSVColor.B = InValue;

	OnValueSelectionChanged().Broadcast(WidgetName, InValue);
}

FReply UGameColorPickerWindow::NativeOnMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent )
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return FReply::Handled();
}

FReply UGameColorPickerWindow::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	return FReply::Handled();
}

FReply UGameColorPickerWindow::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseMove(InGeometry, InMouseEvent);
	
	return FReply::Handled();
}

FReply UGameColorPickerWindow::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	FReply Output = NativeOnFocusReceived(InGeometry, InFocusEvent);

	return Output;
}

void UGameColorPickerWindow::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusLost(InFocusEvent);
}

void UGameColorPickerWindow::NativeOnFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath, const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusChanging(PreviousFocusPath, NewWidgetPath, InFocusEvent);
}
