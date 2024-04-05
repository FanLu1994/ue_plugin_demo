// Copyright Epic Games, Inc. All Rights Reserved.

#include "XiamuWindow.h"
#include "XiamuWindowStyle.h"
#include "XiamuWindowCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName XiamuWindowTabName("XiamuWindow");

#define LOCTEXT_NAMESPACE "FXiamuWindowModule"

void FXiamuWindowModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FXiamuWindowStyle::Initialize();
	FXiamuWindowStyle::ReloadTextures();

	FXiamuWindowCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FXiamuWindowCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FXiamuWindowModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FXiamuWindowModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(XiamuWindowTabName, FOnSpawnTab::CreateRaw(this, &FXiamuWindowModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FXiamuWindowTabTitle", "XiamuWindow"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FXiamuWindowModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FXiamuWindowStyle::Shutdown();

	FXiamuWindowCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(XiamuWindowTabName);
}

TSharedRef<SDockTab> FXiamuWindowModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FXiamuWindowModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("XiamuWindow.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FXiamuWindowModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(XiamuWindowTabName);
}

void FXiamuWindowModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FXiamuWindowCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FXiamuWindowCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FXiamuWindowModule, XiamuWindow)