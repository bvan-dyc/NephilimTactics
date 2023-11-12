#pragma once

#include "Graph/Widgets/SFlowGraphNode.h"

class NEPHEDITOR_API NephFlowNodeWidgetPlayDialogue : public SFlowGraphNode
{
protected:
	
	virtual void UpdateGraphNode() override;

	virtual TSharedRef<SWidget> CreateDialogueContentArea();
	virtual TSharedRef<SWidget> CreateNodeContentArea() override;
	virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;	
	virtual TSharedRef<SWidget> CreateTitleHeader();

public:
	
	SLATE_BEGIN_ARGS(NephFlowNodeWidgetPlayDialogue) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, class UFlowGraphNode* InNode);
	
	/** Used to display the name of the node and allow renaming of the node */
	TSharedPtr<SVerticalBox> TitleBox;
	TSharedPtr<SHorizontalBox> TitleBoxH;
	
	FSlateBrush Brush;

	FSlateColor SpeakerTextColor;

	FSlateColor SpeakerBackgroundColor;
	FSlateBrush SpeakerBackgroundBrush;
	FSlateBrush SpeakerBackgroundCornerBrush;
};
