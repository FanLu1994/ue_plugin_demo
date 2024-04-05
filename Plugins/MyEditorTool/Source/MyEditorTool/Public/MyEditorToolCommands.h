// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "MyEditorToolStyle.h"

class FMyEditorToolCommands : public TCommands<FMyEditorToolCommands>
{
public:

	FMyEditorToolCommands()
		: TCommands<FMyEditorToolCommands>(TEXT("MyEditorTool"), NSLOCTEXT("Contexts", "MyEditorTool", "MyEditorTool Plugin"), NAME_None, FMyEditorToolStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
