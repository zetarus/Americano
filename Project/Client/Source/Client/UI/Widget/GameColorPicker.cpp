// // Copyright 2017-2018 Arcadia Company, Inc. All Rights Reserved.

#include "GameColorPicker.h"
#include "Client.h"

UGameColorPicker::UGameColorPicker(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, ColorPickerIcon(nullptr)
	, ColorWheel(nullptr)
	, bColorWheelClicked(false)
	, H(180.0f)
	, S(0.0f)
	, V(0.5f)
{
}

void UGameColorPicker::NativeConstruct()
{
	Super::NativeConstruct();

	ColorWheel      = Cast< UBorder >(WidgetTree->FindWidget(TEXT("ColorWheel")));
	ColorPickerIcon = Cast< UImage >(WidgetTree->FindWidget(TEXT("ColorPickerIcon")));

	UpdateWidget(true);
}

void UGameColorPicker::SetColor(const FLinearColor& InRGB)
{
	FLinearColor HSV = InRGB.LinearRGBToHSV();
	H = HSV.R;
	S = HSV.G;
	V = HSV.B;

	// Set GameColorPickerPosition from HSV.
	float Theta = FMath::DegreesToRadians(H - 180.0f);
	float Cos = FMath::Cos(Theta);
	float Sin = FMath::Sin(Theta);

	FVector2D Temp(Cos * S, Sin * S);
	ColorPickerIconPosition = Temp * -ColorWheelHalfSize;

	UCanvasPanelSlot* CanvasPanelSlot = Cast< UCanvasPanelSlot >(ColorPickerIcon->Slot);
	CanvasPanelSlot->SetPosition(ColorPickerIconPosition);
}

void UGameColorPicker::UpdateWidget(bool bSaveData/*=false*/)
{
	if (bSaveData)
	{
		GetColorWheelSize();
		return;
	}

	UCanvasPanelSlot* CanvasPanelSlot = Cast< UCanvasPanelSlot >(ColorPickerIcon->Slot);
	CanvasPanelSlot->SetPosition(ColorPickerIconPosition);

	CalculateHueAndSaturation();
	FLinearColor NewColor(H, S, V, 1.0f);
	SelectionChanged.Broadcast(WidgetName, NewColor);
}

FReply UGameColorPicker::NativeOnMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent )
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	ColorPickerIconPosition = CalculateColorPickerIconPosition(InGeometry, InMouseEvent);
	UpdateWidget();

	bColorWheelClicked = true;
	return FReply::Handled();
}

FReply UGameColorPicker::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	bColorWheelClicked = false;

	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
	return FReply::Handled();
}

FReply UGameColorPicker::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseMove(InGeometry, InMouseEvent);
	
	if ( bColorWheelClicked )
	{
		ColorPickerIconPosition = CalculateColorPickerIconPosition(InGeometry, InMouseEvent);
		UpdateWidget();
	}
	return FReply::Handled();
}

void UGameColorPicker::CalculateHueAndSaturation()
{
	UCanvasPanelSlot* CanvasPanelSlot = Cast< UCanvasPanelSlot >(ColorPickerIcon->Slot);
	FVector2D Temp = CanvasPanelSlot->GetPosition() / -ColorWheelHalfSize.X;

	float YDividedByX = FMath::Atan2(Temp.Y, Temp.X);
	H = FMath::RadiansToDegrees(YDividedByX) + 180.0f;
	S = FMath::Sqrt(FMath::Square(Temp.X) + FMath::Square(Temp.Y));
}

void UGameColorPicker::GetColorWheelSize()
{
	UCanvasPanelSlot* CanvasPanelSlot = Cast< UCanvasPanelSlot >(ColorWheel->Slot);
	ColorWheelSize = CanvasPanelSlot->GetSize();
	ColorWheelHalfSize = ColorWheelSize * 0.5f;
}

FVector2D UGameColorPicker::CalculateColorPickerIconPosition(const FGeometry& Geometry, const FPointerEvent& Input)
{
	const FVector2D ScreenSpacePos = Input.GetScreenSpacePosition();
	FVector2D LocalPos = USlateBlueprintLibrary::AbsoluteToLocal(Geometry, ScreenSpacePos);	

	FVector2D TempVector = LocalPos - ColorWheelHalfSize;
	float TempFloat = FMath::Square(TempVector.X / ColorWheelHalfSize.X) + FMath::Square(TempVector.Y / ColorWheelHalfSize.Y);
	TempFloat = FMath::Sqrt(TempFloat);

	FVector2D A;
	A.X = TempVector.X / TempFloat;
	A.Y = TempVector.Y / TempFloat;
	bool PickA = TempFloat > 1;

	FVector2D Output;
	Output.X = UKismetMathLibrary::SelectFloat(A.X, TempVector.X, PickA);
	Output.Y = UKismetMathLibrary::SelectFloat(A.Y, TempVector.Y, PickA);

	return Output;
}