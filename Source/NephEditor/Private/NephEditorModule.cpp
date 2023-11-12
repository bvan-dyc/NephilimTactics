#include "NephEditorModule.h"

#include "NephEditorStyle.h"

void FNephEditorModule::StartupModule()
{
	FNephEditorStyle::Initialize();
	
	RegisterCustomThumbnailRenderers();
}

void FNephEditorModule::ShutdownModule()
{
	FNephEditorStyle::Shutdown();
	
	UnregisterCustomThumbnailRenderers();
}

void FNephEditorModule::RegisterCustomThumbnailRenderers()
{
	
}

void FNephEditorModule::UnregisterCustomThumbnailRenderers()
{
	if (UObjectInitialized())
	{
		
	}
}

IMPLEMENT_PRIMARY_GAME_MODULE(FNephEditorModule, NephEditor, "NephEditor");