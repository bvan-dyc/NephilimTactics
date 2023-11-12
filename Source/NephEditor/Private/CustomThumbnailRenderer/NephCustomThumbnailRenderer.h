#pragma once

#include "CoreMinimal.h"
#include "ThumbnailRendering/BlueprintThumbnailRenderer.h"
#include "NephCustomThumbnailRenderer.generated.h"

UCLASS()
class NEPHEDITOR_API UNephCustomThumbnailRenderer : public UThumbnailRenderer
{
	GENERATED_BODY()

public:

	virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget* RenderTarget, FCanvas* Canvas, bool bAdditionalViewFamily) override;

private:
	
	const UTexture2D* GetIconFromNephAsset(const UDataAsset* dataAsset) const;
	const UTexture2D* GetAssetTypeBackground(const UDataAsset* dataAsset) const;
	const UTexture2D* GetAssetTypeOverlay(const UDataAsset* dataAsset) const;
};
