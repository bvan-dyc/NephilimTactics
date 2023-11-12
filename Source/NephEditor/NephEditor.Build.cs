using UnrealBuildTool;

public class NephEditor : ModuleRules
{
	public NephEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		// ----------------------------------------------------------
		// Public Module Dependencies
		// - Dependencies required in this module's Public Code

		// Unreal: Public Module dependencies
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"UnrealEd", 
			"SlateCore", 
			"Slate", 
			"PropertyEditor",
			"FlowEditor",
			"GraphEditor",
			"StateTreeModule",
			"StateTreeTestSuite",
			"GameplayStateTreeModule",
			"EditorSubsystem"
		});
		
		// Plugin: Private Modules dependencies
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"NephGlitterTactics"
		});
		
		// ----------------------------------------------------------
		// Private Module Dependencies
		// - Dependencies required in this module's Private Code
		
		// Unreal: Private Module dependencies
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Documentation", 
			"Kismet", 
			"UMG", 
			"SubobjectEditor", 
			"SubobjectDataInterface", 
			"AssetTools", 
			"ToolMenus", 
			"Json",
			"InteractiveToolsFramework",
			"EditorInteractiveToolsFramework",
			"InputCore",
			"EditorFramework",
			"UnrealEd",
			"LevelEditor",
			"EditorStyle"
		});
	}
}