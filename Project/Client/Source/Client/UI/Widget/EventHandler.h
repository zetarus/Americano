// // Copyright 2017-2018 Arcadia Company, Inc. All Rights Reserved.

#pragma once

// UnrealEngine
#include "CoreMinimal.h"

/**
 * 
 */
class CLIENT_API FEventHandler
{
public:
};

typedef TArray<FDelegateHandle>					     FDelegateHandleArray;
typedef TMap< FEventHandler*, FDelegateHandleArray > FEventHandlerMap;