#include "NephCustomThumbnailRenderer.h"

#include "CanvasItem.h"

void UNephCustomThumbnailRenderer::Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget* RenderTarget, FCanvas* Canvas, bool bAdditionalViewFamily)
{
	const UDataAsset* DataAsset = Cast<UDataAsset>(Object);
	if (!DataAsset) { return; }

	// Thumbnail Background, should be a square or will just render white
	if (const UTexture2D* AssetBackground = GetAssetTypeBackground(DataAsset))
	{
		FCanvasTileItem backgroundTile(FVector2D(X, Y), AssetBackground->GetResource(), FVector2D(Width, Height), FLinearColor::White);
		backgroundTile.BlendMode = SE_BLEND_Opaque;

		backgroundTile.Draw(Canvas);
	}

	//Thumbnail Icon
	if (const UTexture2D* AssetIcon = GetIconFromNephAsset(DataAsset))
	{
		FCanvasTileItem iconTile(FVector2D(X, Y), AssetIcon->GetResource(), FVector2D(Width, Height), FLinearColor::White);
		iconTile.BlendMode = SE_BLEND_Translucent;

		iconTile.Draw(Canvas);
	}

	//Thumbnnail Overlay, used for easily finding asset types
	if (const UTexture2D* AssetOverlay = GetAssetTypeOverlay(DataAsset))
	{
		FCanvasTileItem overlayTile(FVector2D(X, Y), AssetOverlay->GetResource(), FVector2D(Width, Height), FLinearColor::White);
		overlayTile.BlendMode = SE_BLEND_Translucent;

		overlayTile.Draw(Canvas);
	}
}

const UTexture2D* UNephCustomThumbnailRenderer::GetAssetTypeBackground(const UDataAsset* dataAsset) const
{
	const FString PathToLoad = TEXT("/Game/Editor/Thumbnails/T_BlankThumbnailBackground");
	return Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *(PathToLoad)));
}

const UTexture2D* UNephCustomThumbnailRenderer::GetIconFromNephAsset(const UDataAsset* dataAsset) const
{
	return nullptr;
}

const UTexture2D* UNephCustomThumbnailRenderer::GetAssetTypeOverlay(const UDataAsset* dataAsset) const
{
	return nullptr;
}
