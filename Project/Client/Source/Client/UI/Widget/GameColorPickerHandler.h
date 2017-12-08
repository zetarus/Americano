// // Copyright 2017-2018 Arcadia Company, Inc. All Rights Reserved.

#pragma once

// UnrealEngine
#include "EventHandler.h"

/**
 * 
 */
class CLIENT_API FGameColorPickerHandler : public FEventHandler
{
public:
	virtual void HandleColorPickerColorChanged(FString&, FLinearColor&) = 0;

	virtual void HandleColorPickerBrightnessChanged(FString&, float) = 0;
};
