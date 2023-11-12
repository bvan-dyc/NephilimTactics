#pragma once

#include "Modules/ModuleManager.h"

class FNephEditorModule : public IModuleInterface
{
	
public:
	
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

protected:
	
	void RegisterCustomThumbnailRenderers();
	void UnregisterCustomThumbnailRenderers();
};
