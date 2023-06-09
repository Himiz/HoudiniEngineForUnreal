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

#include "HoudiniEnginePrivatePCH.h"


UHoudiniAssetParameterButton::UHoudiniAssetParameterButton(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{

}


UHoudiniAssetParameterButton::~UHoudiniAssetParameterButton()
{

}


UHoudiniAssetParameterButton*
UHoudiniAssetParameterButton::Create(UHoudiniAssetComponent* InHoudiniAssetComponent, UHoudiniAssetParameter* InParentParameter, 
									 HAPI_NodeId InNodeId, const HAPI_ParmInfo& ParmInfo)
{
	UObject* Outer = InHoudiniAssetComponent;
	if(!Outer)
	{
		Outer = InParentParameter;
		if(!Outer)
		{
			// Must have either component or parent not null.
			check(false);
		}
	}

	UHoudiniAssetParameterButton* HoudiniAssetParameterButton = NewObject<UHoudiniAssetParameterButton>(Outer);

	HoudiniAssetParameterButton->CreateParameter(InHoudiniAssetComponent, InParentParameter, InNodeId, ParmInfo);
	return HoudiniAssetParameterButton;
}


bool
UHoudiniAssetParameterButton::CreateParameter(UHoudiniAssetComponent* InHoudiniAssetComponent, UHoudiniAssetParameter* InParentParameter,
											  HAPI_NodeId InNodeId, const HAPI_ParmInfo& ParmInfo)
{
	if(!Super::CreateParameter(InHoudiniAssetComponent, InParentParameter, InNodeId, ParmInfo))
	{
		return false;
	}

	// We can only handle button type.
	if(HAPI_PARMTYPE_BUTTON != ParmInfo.type)
	{
		return false;
	}

	// Assign internal Hapi values index.
	SetValuesIndex(ParmInfo.intValuesIndex);

	return true;
}


bool
UHoudiniAssetParameterButton::UploadParameterValue()
{
	int32 PressValue = 1;
	if(HAPI_RESULT_SUCCESS != FHoudiniApi::SetParmIntValues(NodeId, &PressValue, ValuesIndex, 1))
	{
		return false;
	}

	return Super::UploadParameterValue();
}


void
UHoudiniAssetParameterButton::CreateWidget(IDetailCategoryBuilder& DetailCategoryBuilder)
{
	Super::CreateWidget(DetailCategoryBuilder);

	FDetailWidgetRow& Row = DetailCategoryBuilder.AddCustomRow(TEXT(""));

	Row.NameWidget.Widget = SNew(STextBlock)
							.ToolTipText(GetParameterLabel())
							.Font(FEditorStyle::GetFontStyle(TEXT("PropertyWindow.NormalFont")));

	TSharedRef<SHorizontalBox> HorizontalBox = SNew(SHorizontalBox);
	TSharedPtr<SButton> Button;

	HorizontalBox->AddSlot().Padding(1, 2, 4, 2)
	[
		SAssignNew(Button, SButton)
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		.Text(GetParameterLabel())
		.ToolTipText(GetParameterLabel())
		.OnClicked(FOnClicked::CreateUObject(this, &UHoudiniAssetParameterButton::OnButtonClick))
	];

	if(Button.IsValid())
	{
		Button->SetEnabled(!bIsDisabled);
	}

	Row.ValueWidget.Widget = HorizontalBox;
	Row.ValueWidget.MinDesiredWidth(FHoudiniAssetComponentDetails::RowValueWidgetDesiredWidth);
}


FReply
UHoudiniAssetParameterButton::OnButtonClick()
{
	MarkPreChanged();
	MarkChanged();

	return FReply::Handled();
}

