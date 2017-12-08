// // Copyright 2017-2018 Arcadia Company, Inc. All Rights Reserved.

#include "CharacterDesigner.h"
#include "Client.h"

UCharacterDesigner::UCharacterDesigner(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, UsrColorPickerSkin(nullptr)
{
}

void UCharacterDesigner::InitSkinColor(const FLinearColor& InRGBColor)
{
	SkinColor = InRGBColor.LinearRGBToHSV();
	CurrentSkinColor = SkinColor;
}

void UCharacterDesigner::InitHairColor(const FLinearColor& InRGBColor)
{
	HairColor = InRGBColor.LinearRGBToHSV();
	CurrentHairColor = HairColor;
}

void UCharacterDesigner::InitIrisColor(const FLinearColor& InRGBColor)
{
	IrisColor = InRGBColor.LinearRGBToHSV();
	CurrentIrisColor = IrisColor;
}

void UCharacterDesigner::OnCharacterColorChanged_Implementation(const FString& InColorName, const FLinearColor& InColor)
{
	
}

void UCharacterDesigner::BeginDestroy()
{
	if ( UsrColorPickerSkin )
	{
		UsrColorPickerSkin->RemoveEventHandler(this);
		UsrColorPickerSkin = nullptr;
	}
	Super::BeginDestroy();
}

void UCharacterDesigner::NativeConstruct()
{
	Super::NativeConstruct();

	UsrColorPickerSkin = Cast< UGameColorPickerWindow >(WidgetTree->FindWidget(TEXT("ColorPickerSkin")));
	if ( UsrColorPickerSkin )
	{
		UsrColorPickerSkin->SetWidgetName("SkinColor");
		UsrColorPickerSkin->SetColorWheelCaption("Skin Color");		
		UsrColorPickerSkin->SetBrightnessCaption("Skin Brightness");
		UsrColorPickerSkin->UpdateWidget();
		UsrColorPickerSkin->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		UsrColorPickerSkin->AddEventHandler( this );
	}

	UsrColorPickerHair = Cast< UGameColorPickerWindow >(WidgetTree->FindWidget(TEXT("ColorPickerHair")));
	if (UsrColorPickerHair)
	{
		UsrColorPickerHair->SetWidgetName("HairColor");
		UsrColorPickerHair->SetColorWheelCaption("Hair Color");
		UsrColorPickerHair->SetBrightnessCaption("Hair Brightness");
		UsrColorPickerHair->UpdateWidget();
		UsrColorPickerHair->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		UsrColorPickerHair->AddEventHandler(this);
	}

	UsrColorPickerIris = Cast< UGameColorPickerWindow >(WidgetTree->FindWidget(TEXT("ColorPickerIris")));
	if (UsrColorPickerIris)
	{
		UsrColorPickerIris->SetWidgetName("IrisColor");
		UsrColorPickerIris->SetColorWheelCaption("Iris Color");
		UsrColorPickerIris->SetBrightnessCaption("Iris Brightness");
		UsrColorPickerIris->UpdateWidget();
		UsrColorPickerIris->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		UsrColorPickerIris->AddEventHandler(this);
	}
}

void UCharacterDesigner::HandleColorPickerColorChanged(FString& InColorName, FLinearColor& InColor)
{
	FString		 OutColorName;
	FLinearColor OutColorValue;

	if (InColorName == TEXT("SkinColor"))
	{
		OutColorName = TEXT("CurrentSkinColor");
		CurrentSkinColor.R = InColor.R;
		CurrentSkinColor.G = InColor.G;
		CurrentSkinColor.B = InColor.B;
		OutColorValue = CurrentSkinColor.HSVToLinearRGB();
	}
	else if (InColorName == TEXT("HairColor"))
	{
		OutColorName = TEXT("CurrentHairColor");
		CurrentHairColor.R = InColor.R;
		CurrentHairColor.G = InColor.G;
		CurrentHairColor.B = InColor.B;
		OutColorValue = CurrentHairColor.HSVToLinearRGB();
	}
	else if (InColorName == TEXT("IrisColor"))
	{
		OutColorName = TEXT("CurrentIrisColor");
		CurrentIrisColor.R = InColor.R;
		CurrentIrisColor.G = InColor.G;
		CurrentIrisColor.B = InColor.B;
		OutColorValue = CurrentIrisColor.HSVToLinearRGB();
	}	
	OnCharacterColorChanged(OutColorName, OutColorValue);
}

void UCharacterDesigner::HandleColorPickerBrightnessChanged(FString& InColorName, float InColorValue)
{
	FString		 OutColorName;
	FLinearColor OutColorValue;

	if (InColorName == TEXT("SkinColor"))
	{
		CurrentSkinColor.B = InColorValue;
		OutColorName = TEXT("CurrentSkinColor");
		OutColorValue = CurrentSkinColor.HSVToLinearRGB();
	}
	else if (InColorName == TEXT("HairColor"))
	{
		CurrentHairColor.B = InColorValue;
		OutColorName = TEXT("CurrentHairColor");
		OutColorValue = CurrentHairColor.HSVToLinearRGB();
	}
	else if (InColorName == TEXT("IrisColor"))
	{
		CurrentIrisColor.B = InColorValue;
		OutColorName = TEXT("CurrentIrisColor");
		OutColorValue = CurrentIrisColor.HSVToLinearRGB();
	}
	OnCharacterColorChanged(OutColorName, OutColorValue);
}