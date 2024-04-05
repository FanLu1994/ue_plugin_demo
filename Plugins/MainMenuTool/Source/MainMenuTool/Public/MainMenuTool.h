// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FMainMenuToolModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void OnTestBtnClick();
	void OpenDialog();
	void OpenWindow();
	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);
	
#pragma region MainBarExtend
	// 初始化
	void InitMainBarByExtend();
	// 添加按钮
	void AddOneEntry(class FMenuBuilder& MenuBuilder);
	// 添加菜单
	void AddOneMenuBarEntry(class FMenuBarBuilder& MenuBarBuilder);
	void AddMenuOne(class FMenuBuilder& MenuBuilder);
	// void AddMenuTwo(class FMenuBuilder& MenuBuilder);
	// void AddMenuThree(class FMenuBuilder& MenuBuilder);
	
#pragma endregion 


#pragma region ToolBarExtend
    // 初始化
    void InitToolBarByExtend();
    // 添加按钮
    void OpenBlueprint();
#pragma endregion
};
