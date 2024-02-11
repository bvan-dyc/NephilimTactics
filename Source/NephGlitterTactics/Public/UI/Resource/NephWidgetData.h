#pragma once

#include "CoreMinimal.h"

struct FNephWidgetData
{
public:

    TWeakObjectPtr<class UNepHUDWidget> HUDWidget;
    TWeakObjectPtr<class UNephInteractionMenuWidget> InteractionMenuWidget;
    TWeakObjectPtr<class UNephConversationWidget> ConversationWidget;
    TWeakObjectPtr<class UNephCutsceneConversationWidget> CutsceneConversationWidget;
    
    bool bUIVisible = false;

public:

    FNephWidgetData();
    
    static FNephWidgetData* Get(const UObject* context);
};
