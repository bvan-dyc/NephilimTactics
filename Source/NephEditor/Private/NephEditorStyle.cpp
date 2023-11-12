#include "NephEditorStyle.h"

#include "Styling/SlateStyleRegistry.h"
#include "Styling/SlateTypes.h"

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( FNephEditorStyle::InContent( RelativePath, ".png" ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( StyleSet->RootToContentDir( RelativePath, TEXT( ".png" ) ), __VA_ARGS__ )
#define TTF_CORE_FONT( RelativePath, ... ) FSlateFontInfo( StyleSet->RootToCoreContentDir( RelativePath, TEXT( ".ttf" ) ), __VA_ARGS__ )

#define EDITOR_IMAGE_BRUSH_SVG( RelativePath, ... ) FSlateVectorImageBrush( FNephEditorStyle::InContent( RelativePath, ".svg" ), __VA_ARGS__ )

TSharedPtr<FSlateStyleSet> FNephEditorStyle::StyleSet = nullptr;


FString FNephEditorStyle::InContentRoot()
{
	return FPaths::ProjectContentDir() / TEXT("Editor") / TEXT("Slate");
}

FString FNephEditorStyle::InContent( const FString& RelativePath, const ANSICHAR* Extension )
{
	static FString ContentDir = InContentRoot(); // stores it in static to be faster
	return ( ContentDir / RelativePath ) + Extension;
}

void FNephEditorStyle::Initialize()
{
	// Only register once
	if( StyleSet.IsValid() )
	{
		return;
	}

	StyleSet = MakeShared<FSlateStyleSet>( GetStyleSetName() );

	StyleSet->SetContentRoot(InContentRoot() / TEXT("Editor/Slate"));
	StyleSet->SetCoreContentRoot(InContentRoot() / TEXT("Editor"));

	const FVector2D Icon16x16(16.0f, 16.0f);
	const FVector2D Icon20x20(20.0f, 20.0f);
	const FVector2D Icon40x40(40.0f, 40.0f);
	const FVector2D Icon48x48(48.0f, 48.0f);
	const FVector2D Icon64x64(64.0f, 64.0f);
	const FVector2D Icon512x512(512.0f, 512.0f);

	StyleSet->Set("HexMapEditor.ModeIcon", new EDITOR_IMAGE_BRUSH_SVG("HexMapEditorModeIcon", Icon20x20));
	StyleSet->Set("HexMapEditor.Paint.ToolIcon", new IMAGE_BRUSH("HexPaintToolIcon", Icon20x20));
	StyleSet->Set("HexMapEditor.Sculpt.ToolIcon", new IMAGE_BRUSH("HexSculptToolIcon", Icon20x20));
	StyleSet->Set("HexMapEditor.Generate.ToolIcon", new EDITOR_IMAGE_BRUSH_SVG("HexGenerateToolIcon", Icon20x20));
	StyleSet->Set("HexMapEditor.Placer.ToolIcon", new EDITOR_IMAGE_BRUSH_SVG("HexPlacerToolIcon", Icon20x20));
	StyleSet->Set("HexMapEditor.ZonePainter.ToolIcon", new IMAGE_BRUSH("ZonePaintToolIcon", Icon20x20));
	StyleSet->Set("HexMapEditor.Decorate.ToolIcon", new IMAGE_BRUSH("DecorateToolIcon", Icon20x20));

	FSlateStyleRegistry::RegisterSlateStyle( *StyleSet.Get() );
}

void FNephEditorStyle::Shutdown()
{
	if (StyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
		ensure(StyleSet.IsUnique());
		StyleSet.Reset();
	}
}

const FName& FNephEditorStyle::GetStyleSetName()
{
	static FName StyleName(TEXT("NephEditorStyle"));
	return StyleName;
}

#undef EDITOR_IMAGE_BRUSH_SVG
