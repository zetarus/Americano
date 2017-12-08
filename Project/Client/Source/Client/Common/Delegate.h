// // Copyright 2017-2018 Arcadia Company, Inc. All Rights Reserved.

#pragma once

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnColorPickerSelectionChanged, FString&, FLinearColor&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnValueSelectionChanged, FString&, float);