#pragma once

struct FNepUnitsSetup
{
	static void Setup(
		class FArcUniverse& Universe,
		struct FArcScheduleBuilder& InitScheduleBuilder,
		struct FArcScheduleBuilder& TickScheduleBuilder
	);
	
	static void SetupForEditor(
		class FArcUniverse& Universe,
		struct FArcScheduleBuilder& InitScheduleBuilder,
		struct FArcScheduleBuilder& TickScheduleBuilder
	);
};
