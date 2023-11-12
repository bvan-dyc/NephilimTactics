#pragma once

#include "Nodes/FlowNode.h"

#include "NephFlowNode.generated.h"

UCLASS(Abstract, Blueprintable, HideCategories = Object)
class NEPHGLITTERTACTICS_API UNephFlowNode : public UFlowNode
{
	GENERATED_BODY()

public:

	UNephFlowNode() {}
};
