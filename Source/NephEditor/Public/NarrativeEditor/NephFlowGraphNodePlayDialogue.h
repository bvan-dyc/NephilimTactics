#pragma once

#include "Graph/Nodes/FlowGraphNode.h"

#include "NephFlowGraphNodePlayDialogue.generated.h"

UCLASS()
class NEPHEDITOR_API UNephFlowGraphNodePlayDialogue : public UFlowGraphNode
{
	GENERATED_BODY()

public:
	
	UNephFlowGraphNodePlayDialogue();
	
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
};