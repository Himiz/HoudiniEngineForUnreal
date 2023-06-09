/*
 * PROPRIETARY INFORMATION.  This software is proprietary to
 * Side Effects Software Inc., and is not to be reproduced,
 * transmitted, or disclosed in any way without written permission.
 *
 * Produced by:
 *      Mykola Konyk
 *      Side Effects Software Inc
 *      123 Front Street West, Suite 1401
 *      Toronto, Ontario
 *      Canada   M5J 2M2
 *      416-504-9876
 *
 */

#pragma once
#include "HoudiniAssetThumbnailRenderer.generated.h"


class UObject;
class FCanvas;
class FRenderTarget;
class UHoudiniAsset;
class FHoudiniAssetThumbnailScene;


UCLASS(config = Editor)
class HOUDINIENGINE_API UHoudiniAssetThumbnailRenderer : public UDefaultSizedThumbnailRenderer
{
	GENERATED_UCLASS_BODY()

/** ThumbnailRenderer methods. **/
public:

	virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget* RenderTarget, FCanvas* Canvas) override;

/** UObject methods. **/
public:

	virtual void BeginDestroy() override;

public:

	/** Called when asset no longer needs thumbnail rendering. Typically when asset is deleted from content browser. **/
	void RemoveAssetThumbnail(UHoudiniAsset* HoudiniAsset);

private:

	/** Map of scenes managed by this thumbnail renderer, one for each asset. **/
	TMap<UHoudiniAsset*, FHoudiniAssetThumbnailScene*> ThumbnailScenes;
};
