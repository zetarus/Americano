// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameWidget.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UGameWidget(const FObjectInitializer& ObjectInitializer);

	//UObject interface
	virtual void BeginDestroy() override;
	//~ End UObject Interface
};
