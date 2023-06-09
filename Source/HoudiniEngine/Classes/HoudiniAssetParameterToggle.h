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
#include "HoudiniAssetParameterToggle.generated.h"


UCLASS()
class HOUDINIENGINE_API UHoudiniAssetParameterToggle : public UHoudiniAssetParameter
{
	GENERATED_UCLASS_BODY()

public:

	/** Destructor. **/
	virtual ~UHoudiniAssetParameterToggle();

public:

	/** Create sintance of this class. **/
	static UHoudiniAssetParameterToggle* Create(UHoudiniAssetComponent* InHoudiniAssetComponent, UHoudiniAssetParameter* InParentParameter, HAPI_NodeId InNodeId, const HAPI_ParmInfo& ParmInfo);

public:

	/** Create this parameter from HAPI information. **/
	virtual bool CreateParameter(UHoudiniAssetComponent* InHoudiniAssetComponent, UHoudiniAssetParameter* InParentParameter, HAPI_NodeId InNodeId, const HAPI_ParmInfo& ParmInfo) override;

	/** Create widget for this parameter and add it to a given category. **/
	virtual void CreateWidget(IDetailCategoryBuilder& DetailCategoryBuilder) override;

	/** Create widget for this parameter inside a given box. **/
	virtual void CreateWidget(TSharedPtr<SVerticalBox> VerticalBox);

	/** Upload parameter value to HAPI. **/
	virtual bool UploadParameterValue() override;

/** UObject methods. **/
public:

	virtual void Serialize(FArchive& Ar) override;

public:

	/** Get value of this property, used by Slate. **/
	void CheckStateChanged(ESlateCheckBoxState::Type NewState, int32 Idx);

	/** Return checked state of this property, used by Slate. **/
	ESlateCheckBoxState::Type IsChecked(int32 Idx) const;

protected:

	/** Values of this property. **/
	TArray<int32> Values;
};
