// Copyright Epic Games, Inc. All Rights Reserved.

#include "MainMenuTool.h"

#include "LevelEditor.h"
#include "ToolMenu.h"
#include "ToolMenus.h"
#include "Misc/MessageDialog.h"
#include "Widgets/Docking/SDockTab.h"

#define LOCTEXT_NAMESPACE "FMainMenuToolModule"

static const FName MainWindowName("MyWindow");

void FMainMenuToolModule::StartupModule()
{
	InitMainBarByExtend();
	InitToolBarByExtend();
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MainWindowName, FOnSpawnTab::CreateRaw(this, &FMainMenuToolModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FMainMenuToolModule", "MyWindow"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FMainMenuToolModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FMainMenuToolModule::OnTestBtnClick()
{
	UE_LOG(LogTemp,Log,TEXT("Test Button Clicked"));
}

void FMainMenuToolModule::OpenDialog()
{
	FText DialogText = FText::Format(
						LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
						FText::FromString(TEXT("FMyEditorToolModule::PluginButtonClicked()")),
						FText::FromString(TEXT("MyEditorTool.cpp"))
				   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FMainMenuToolModule::OpenWindow()
{
	FGlobalTabmanager::Get()->TryInvokeTab(MainWindowName);
}

// 弹出窗口
TSharedRef<SDockTab> FMainMenuToolModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
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

#pragma region MainBarExtend
void FMainMenuToolModule::InitMainBarByExtend()
{
	TSharedPtr<FExtender> MainBarExtender = MakeShareable(new FExtender);
	MainBarExtender->AddMenuExtension(
		"Support",
		EExtensionHook::After,
		nullptr,
		FMenuExtensionDelegate::CreateRaw(this,&FMainMenuToolModule::AddOneEntry)
		);

		
	MainBarExtender->AddMenuBarExtension(
	       "Help",
	       EExtensionHook::After,
	       nullptr,
	       FMenuBarExtensionDelegate::CreateRaw(this,&FMainMenuToolModule::AddOneMenuBarEntry)
	       );
	
	// 必须添加到编辑器中
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	TSharedPtr<FExtensibilityManager> MenuExtensibilityManager = LevelEditorModule.GetMenuExtensibilityManager();
	MenuExtensibilityManager->AddExtender(MainBarExtender);
}

void FMainMenuToolModule::AddOneEntry(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		FText::FromString("Test"),
		FText::FromString("提示信息"),
		FSlateIcon(),
		// FUIAction(FExecuteAction::CreateRaw(this,&FMainMenuToolModule::OnTestBtnClick))
		FUIAction(FExecuteAction::CreateRaw(this,&FMainMenuToolModule::OnTestBtnClick))
		
	);
	MenuBuilder.AddSeparator(); // 添加分隔符
	
}

void FMainMenuToolModule::AddOneMenuBarEntry(FMenuBarBuilder& MenuBarBuilder)
{
		MenuBarBuilder.AddPullDownMenu(
			FText::FromString("OneMenu"),
			FText::FromString("扩展菜单"),
			FNewMenuDelegate::CreateRaw(this,&FMainMenuToolModule::AddMenuOne),
			"oneMenu"
			);
}

void FMainMenuToolModule::AddMenuOne(FMenuBuilder& MenuBuilder)
{
	// 添加菜单
		MenuBuilder.BeginSection("section1",FText::FromString("Section1"));
		MenuBuilder.AddMenuEntry(
			FText::FromString("MenuOne"),
			FText::FromString("menu one"),
			FSlateIcon(),
			FUIAction(FExecuteAction::CreateRaw(this,&FMainMenuToolModule::OpenWindow))
		);
	// 添加子菜单
		MenuBuilder.AddSubMenu(
			FText::FromString("SubMenu"),
			FText::FromString("my submenu position"),
			FNewMenuDelegate::CreateRaw(this,&FMainMenuToolModule::AddOneEntry)
		);
		MenuBuilder.EndSection();
}
#pragma endregion

#pragma region ToolBarExtend
void FMainMenuToolModule::InitToolBarByExtend()
{
	FToolMenuOwnerScoped OwnerScoped(this); // 不加这行，UtoolMenus会报错
	UToolMenu* Menu =  UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.User");
	FToolMenuSection& Section = Menu->FindOrAddSection(NAME_None);
	Section.AddEntry
	(
		FToolMenuEntry::InitToolBarButton(
			"First Button Test",
			FToolUIActionChoice(FExecuteAction::CreateRaw(this,&FMainMenuToolModule::OpenBlueprint)),
			FText::FromString("Label::mytest"),
			FText::FromString("Tooltip::mytest"),
			FSlateIcon()
			)
	);	
	
}

void FMainMenuToolModule::OpenBlueprint()
{
	UE_LOG(LogTemp,Log,TEXT("Open Blueprint %s"),*(FDateTime::Now().ToString()));
}
#pragma endregion

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMainMenuToolModule, MainMenuTool)