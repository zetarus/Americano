// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "VREditorAutoScaler.h"
#include "VREditorMode.h"
#include "ViewportInteractionTypes.h"
#include "ViewportWorldInteraction.h"
#include "ViewportInteractor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/WorldSettings.h"
#include "Sound/SoundCue.h"

namespace VREd
{
	static FAutoConsoleVariable AllowResetScale(TEXT("VREd.AllowResetScale"), 1, TEXT("Allowed to reset world to meters to default world to meters"));
}

UVREditorAutoScaler::UVREditorAutoScaler( const FObjectInitializer& ObjectInitializer ) :
	Super( ObjectInitializer ),
	VRMode( nullptr )
{
	// Load sounds
	ScaleSound = LoadObject<USoundCue>( nullptr, TEXT( "/Engine/VREditor/Sounds/VR_teleport_Cue" ) );
	check( ScaleSound != nullptr );
}


void UVREditorAutoScaler::Init( class UVREditorMode* InVRMode )
{
	VRMode = InVRMode;
	VRMode->GetWorldInteraction().OnViewportInteractionInputAction().AddUObject( this, &UVREditorAutoScaler::OnInteractorAction );
}


void UVREditorAutoScaler::Shutdown()
{
	VRMode->GetWorldInteraction().OnViewportInteractionInputAction().RemoveAll( this );
	VRMode = nullptr;
}


void UVREditorAutoScaler::Scale( const float NewWorldToMetersScale )
{
	if (VREd::AllowResetScale->GetInt() != 0)
	{
		UViewportWorldInteraction* WorldInteraction = &VRMode->GetWorldInteraction();

		// Set the new world to meters scale.
		WorldInteraction->SetWorldToMetersScale( NewWorldToMetersScale, true );
		WorldInteraction->SkipInteractiveWorldMovementThisFrame();
		UGameplayStatics::PlaySound2D( VRMode->GetWorld(), ScaleSound );
	}
}


void UVREditorAutoScaler::OnInteractorAction( class FEditorViewportClient& ViewportClient, UViewportInteractor* Interactor, const struct FViewportActionKeyInput& Action, bool& bOutIsInputCaptured, bool& bWasHandled )
{
	if (VREd::AllowResetScale->GetInt() != 0)
	{
		if( Action.ActionType == VRActionTypes::ConfirmRadialSelection )
		{
			if( Action.Event == IE_Pressed )
			{
				const EViewportInteractionDraggingMode DraggingMode = Interactor->GetDraggingMode();
				UViewportInteractor* OtherInteractor = Interactor->GetOtherInteractor();

				// Start dragging at laser impact when already dragging actors freely
				if( DraggingMode == EViewportInteractionDraggingMode::World ||
					( DraggingMode == EViewportInteractionDraggingMode::AssistingDrag && OtherInteractor != nullptr && OtherInteractor->GetDraggingMode() == EViewportInteractionDraggingMode::World ) )
				{
					const float DefaultWorldToMetersScale = VRMode->GetSavedEditorState().WorldToMetersScale;
					Scale( DefaultWorldToMetersScale );

					bWasHandled = true;
					bOutIsInputCaptured = true;
				}
			}
			else if( Action.Event == IE_Released )
			{
				bOutIsInputCaptured = false;
			}
		}
	}
}
