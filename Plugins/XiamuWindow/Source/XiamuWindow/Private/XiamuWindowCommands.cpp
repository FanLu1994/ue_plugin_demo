// Copyright Epic Games, Inc. All Rights Reserved.

#include "XiamuWindowCommands.h"

#define LOCTEXT_NAMESPACE "FXiamuWindowModule"

void FXiamuWindowCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "XiamuWindow", "Bring up XiamuWindow window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
