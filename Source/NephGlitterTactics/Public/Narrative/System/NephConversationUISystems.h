#pragma once

#include "ArcRes.h"
#include "Narrative/Resource/NephNarrativeEvents.h"
#include "UI\Resource\NephWidgetData.h"

struct FNephConversationUISystems
{
	
public:
	
	static void ConversationPanelTick(FArcRes<FNephWidgetData> WidgetData, FArcRes<FNephNarrativeEvents> NarrativeEvents);
	static void CutscenePanelTick(FArcRes<FNephWidgetData> WidgetData, FArcRes<FNephNarrativeEvents> NarrativeEvents);
};
