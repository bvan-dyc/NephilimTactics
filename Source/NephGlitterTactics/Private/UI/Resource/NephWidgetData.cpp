#include "UI/Resource/NephWidgetData.h"
#include "ArcECSSubsystem.h"

FNephWidgetData::FNephWidgetData()
	//: WidgetUpdateManager(MakeShared<FNepWidgetUpdateManager>())
{}

FNephWidgetData* FNephWidgetData::Get(const UObject* context)
{
	UArcECSSubsystem* ECSSubsystem = UArcECSSubsystem::Get(context);
	FArcUniverse* Universe = ECSSubsystem ? &ECSSubsystem->GetUniverse() : nullptr;
	return Universe ? Universe->GetResource<FNephWidgetData>() : nullptr;
}
