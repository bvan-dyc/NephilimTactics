
#include "NarrativeEditor\NephFlowNodeWidgetPlayDialogue.h"

#include "FlowEditorStyle.h"
#include "GraphEditorSettings.h"
#include "SCommentBubble.h"
#include "TutorialMetaData.h"
#include "Narrative/Flow/NephFlowNodePlayDialogue.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"

void NephFlowNodeWidgetPlayDialogue::UpdateGraphNode()
{
	InputPins.Empty();
	OutputPins.Empty();

	// Reset variables that are going to be exposed, in case we are refreshing an already setup node.
	RightNodeBox.Reset();
	LeftNodeBox.Reset();

	TSharedPtr<SVerticalBox> MainVerticalBox;
	SetupErrorReporting();

	const TSharedPtr<SNodeTitle> NodeTitle = SNew(SNodeTitle, GraphNode);

	// Get node icon
	IconColor = FLinearColor::White;
	const FSlateBrush* IconBrush = nullptr;
	if (GraphNode && GraphNode->ShowPaletteIconOnNode())
	{
		IconBrush = GraphNode->GetIconAndTint(IconColor).GetOptionalIcon();
	}

	const TSharedRef<SOverlay> DefaultTitleAreaWidget = SNew(SOverlay)
		+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Center)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
					.HAlign(HAlign_Fill)
					[
						SNew(SBorder)
							.BorderImage(FFlowEditorStyle::GetBrush("Flow.Node.Title"))
							// The extra margin on the right is for making the color spill stretch well past the node title
							.Padding(FMargin(10, 5, 30, 3))
							.BorderBackgroundColor(this, &SGraphNode::GetNodeTitleColor)
							[
								SNew(SHorizontalBox)
								+ SHorizontalBox::Slot()
									.VAlign(VAlign_Top)
									.Padding(FMargin(0.f, 0.f, 4.f, 0.f))
									.AutoWidth()
									[
										SNew(SImage)
											.Image(IconBrush)
											.ColorAndOpacity(this, &SGraphNode::GetNodeTitleIconColor)
									]
								+ SHorizontalBox::Slot()
									[
										SNew(SVerticalBox)
										+ SVerticalBox::Slot()
											.AutoHeight()
											[
												CreateTitleWidget(NodeTitle)
											]
										+ SVerticalBox::Slot()
											.AutoHeight()
											[
												NodeTitle.ToSharedRef()
											]
									]
							]
					]
			];

	// Setup a meta tag for this node
	FGraphNodeMetaData TagMeta(TEXT("FlowGraphNode"));
	PopulateMetaTag(&TagMeta);

	this->ContentScale.Bind(this, &SGraphNode::GetContentScale);

	const TSharedPtr<SVerticalBox> InnerVerticalBox = SNew(SVerticalBox)
		+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Top)
			[
				CreateNodeContentArea()
			];

	const TSharedPtr<SWidget> EnabledStateWidget = GetEnabledStateWidget();
	if (EnabledStateWidget.IsValid())
	{
		InnerVerticalBox->AddSlot()
			.AutoHeight()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Top)
			.Padding(FMargin(2, 0))
			[
				EnabledStateWidget.ToSharedRef()
			];
	}

	InnerVerticalBox->AddSlot()
		.AutoHeight()
		.Padding(Settings->GetNonPinNodeBodyPadding())
		[
			ErrorReporting->AsWidget()
		];

	this->GetOrAddSlot(ENodeZone::Center)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SAssignNew(MainVerticalBox, SVerticalBox)
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Left)
				.AutoHeight()
				[	
					CreateTitleHeader()
				]
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.AutoHeight()
				[
					SNew(SOverlay)
						.AddMetaData<FGraphNodeMetaData>(TagMeta)
						+ SOverlay::Slot()
							.Padding(Settings->GetNonPinNodeBodyPadding())
							[
								SNew(SImage)
									.Image(GetNodeBodyBrush())
									.ColorAndOpacity(this, &SGraphNode::GetNodeBodyColor)
							]
						+ SOverlay::Slot()
							[
								InnerVerticalBox.ToSharedRef()
							]
				]
		];

	if (GraphNode && GraphNode->SupportsCommentBubble())
	{
		// Create comment bubble
		TSharedPtr<SCommentBubble> CommentBubble;
		const FSlateColor CommentColor = GetDefault<UGraphEditorSettings>()->DefaultCommentNodeTitleColor;

		SAssignNew(CommentBubble, SCommentBubble)
			.GraphNode(GraphNode)
			.Text(this, &SGraphNode::GetNodeComment)
			.OnTextCommitted(this, &SGraphNode::OnCommentTextCommitted)
			.OnToggled(this, &SGraphNode::OnCommentBubbleToggled)
			.ColorAndOpacity(CommentColor)
			.AllowPinning(true)
			.EnableTitleBarBubble(true)
			.EnableBubbleCtrls(true)
			.GraphLOD(this, &SGraphNode::GetCurrentLOD)
			.IsGraphNodeHovered(this, &SGraphNode::IsHovered);

		GetOrAddSlot(ENodeZone::TopCenter)
			.SlotOffset(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetOffset))
			.SlotSize(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetSize))
			.AllowScaling(TAttribute<bool>(CommentBubble.Get(), &SCommentBubble::IsScalingAllowed))
			.VAlign(VAlign_Top)
			[
				CommentBubble.ToSharedRef()
			];
	}

	CreateBelowWidgetControls(MainVerticalBox);
	CreatePinWidgets();
	CreateInputSideAddButton(LeftNodeBox);
	CreateOutputSideAddButton(RightNodeBox);
//	CreateBelowPinControls(InnerVerticalBox);
	CreateAdvancedViewArrow(InnerVerticalBox);
}

TSharedRef<SWidget> NephFlowNodeWidgetPlayDialogue::CreateDialogueContentArea()
{
	UFlowNode* FlowNode = FlowGraphNode->GetFlowNode();
	const UNephFlowNodePlayDialogue* DialogueNode = Cast<UNephFlowNodePlayDialogue>(FlowNode);
	if (!FlowNode || !DialogueNode)
	{
		return SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.Padding(10.f)
					[
						SNew(STextBlock)
						.Text(FText::FromString("This node seems to be broken. Please recreate it!"))
						.WrapTextAt(370.f)
					];
	}
	
	bool bShowPortrait = false;
	Brush.ImageSize = FVector2D(64,64);

	if (UTexture2D* Portrait = DialogueNode->GetSpeakerPortrait())
	{
		bShowPortrait = true;
		Brush.SetResourceObject(Portrait);	
	}

	const FText DialogueText = DialogueNode->GetReadableDialogueString();
	
	if (bShowPortrait)
	{
		return SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			  .HAlign(HAlign_Left)
			  .VAlign(VAlign_Bottom)
			  .AutoWidth()
			  .Padding(0.f)
			[
				SNew(SImage)
				.Image(&Brush)
			]
						
			+ SHorizontalBox::Slot()
			  .HAlign(HAlign_Fill)
			  .VAlign(VAlign_Center)
			  .FillWidth(1.0f)
			  .Padding(10.f)
			[
				SNew(STextBlock)
								.Text(DialogueText)
								.WrapTextAt(250.f)
			];
	}

	return SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			  .VAlign(VAlign_Center)
			  .Padding(10.f)
			[
				SNew(STextBlock)
								.Text(DialogueText)
								.WrapTextAt(250.f)
			];
}

TSharedRef<SWidget> NephFlowNodeWidgetPlayDialogue::CreateNodeContentArea()
{
	return SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush("NoBorder"))
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			.AutoWidth()
			[
				SAssignNew(LeftNodeBox, SVerticalBox)
			]
			+SHorizontalBox::Slot()
			.HAlign(HAlign_Center)
			.FillWidth(1.0f)
			[
				CreateDialogueContentArea()
			]
			+SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Center)
			[
				SAssignNew(RightNodeBox, SVerticalBox)
			]
		];
}

void NephFlowNodeWidgetPlayDialogue::CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox)
{
	UFlowNode* FlowNode = FlowGraphNode->GetFlowNode();
	if (!FlowNode) { return; }
	const UNephFlowNodePlayDialogue* DialogueNode = Cast<UNephFlowNodePlayDialogue>(FlowNode);
	if (!DialogueNode) { return; }

	const FText DialogueText = DialogueNode->GetReadableDialogueString();

	MainBox->AddSlot()
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		.FillWidth(1.0f)
		.Padding(10.f)
		[
			SNew(STextBlock)
			.Text(DialogueText)
			.WrapTextAt(250.f)
		]
	];
}

TSharedRef<SWidget> NephFlowNodeWidgetPlayDialogue::CreateTitleHeader()
{
	FText NodeTitleText = FText::FromString("Speaker is invalid!");
	FLinearColor SpeakerColor = FLinearColor::Gray;
	
	if (UFlowNode* FlowNode = FlowGraphNode->GetFlowNode())
	{
		const UNephFlowNodePlayDialogue* DialogueNode = Cast<UNephFlowNodePlayDialogue>(FlowNode);
		{
			NodeTitleText = DialogueNode->GetSpeakerName();
			SpeakerColor = DialogueNode->GetSpeakerColor();
		}
	}

	SpeakerBackgroundBrush.DrawAs = ESlateBrushDrawType::Box;
	SpeakerBackgroundBrush.TintColor = SpeakerColor;

	SpeakerBackgroundCornerBrush.DrawAs = ESlateBrushDrawType::Box;
	SpeakerBackgroundCornerBrush.TintColor = SpeakerColor;
	
	SAssignNew(TitleBoxH, SHorizontalBox)
	+SHorizontalBox::Slot()
	.AutoWidth()
	.Padding(10.f,0.f,0.f,0.f)
	.VAlign(VAlign_Fill)
	[
		SNew(SBorder)
		.BorderImage(&SpeakerBackgroundBrush)
		.Padding(FMargin(10.f, 4.f))
		.VAlign(VAlign_Fill)
		[
			SAssignNew(InlineEditableText, SInlineEditableTextBlock)
				.Style(FAppStyle::Get(), "Graph.Node.NodeTitleInlineEditableText")
				.Text(NodeTitleText)
				.ColorAndOpacity(SpeakerTextColor)
				.IsReadOnly(true)
				.IsSelected(this, &NephFlowNodeWidgetPlayDialogue::IsSelectedExclusively)
		]
	];

	return TitleBoxH.ToSharedRef();
}

void NephFlowNodeWidgetPlayDialogue::Construct(const FArguments& InArgs, UFlowGraphNode* InNode)
{
	SpeakerTextColor = FLinearColor::White;
	
	GraphNode = InNode;
	FlowGraphNode = InNode;

	SetCursor(EMouseCursor::CardinalCross);
	UpdateGraphNode();
}
