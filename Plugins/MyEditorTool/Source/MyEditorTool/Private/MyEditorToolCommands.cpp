// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyEditorToolCommands.h"

#define LOCTEXT_NAMESPACE "FMyEditorToolModule"

void FMyEditorToolCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "MyEditorTool", "Execute MyEditorTool action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
