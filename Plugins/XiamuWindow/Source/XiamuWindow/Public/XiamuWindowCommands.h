// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "XiamuWindowStyle.h"

class FXiamuWindowCommands : public TCommands<FXiamuWindowCommands>
{
public:

	FXiamuWindowCommands()
		: TCommands<FXiamuWindowCommands>(TEXT("XiamuWindow"), NSLOCTEXT("Contexts", "XiamuWindow", "XiamuWindow Plugin"), NAME_None, FXiamuWindowStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};